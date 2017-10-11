#include <stdio.h>
#include "gst_player.h"

GstPlayer::GstPlayer()
    : state_(STATE_NULL) {
}

GstPlayer::GstPlayer(const std::string& file_path, const std::string& sink, bool sync, guintptr xwinid)
    : file_path_(file_path)
    , sink_(sink)
    , sync_(sync)
    , xwinid_(xwinid)
    , state_(STATE_NULL) {
    Init();
}

GstPlayer::~GstPlayer() {
    if(state_ != STATE_READY) {
        stop();
    }

    Release();
}

bool GstPlayer::open(const std::string& file_path, const std::string& sink, bool sync, guintptr xwinid) {

    if (state_ != STATE_NULL) return false;

    file_path_ = file_path;
    sink_ = sink;
    sync_ = sync;
    xwinid_ = xwinid;

    return Init();
}

bool GstPlayer::play() {
    if (state_ == STATE_PLAYING) {
        return true;
    }
    else if (state_ == STATE_NULL) {
        Init();
    }

    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if(GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: playing.\n");
        state_ = STATE_PLAYING;
        return true;
    }
    else {
        printf("-- GST: Failed to play.\n");
        Release();
    }

    return false;
}

bool GstPlayer::pause() {
    if (state_ != STATE_PLAYING) {
        printf("-- GST: Is not playing, can not pause.\n");
        return false;
    }

    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PAUSED);
    if (GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: paused.\n");
        state_ = STATE_PAUSED;
        return true;
    }
    else {
        printf("-- GST: Failed to pause.\n");
    }

    return false;
}

bool GstPlayer::stop() {
    if (state_ == STATE_NULL) {
        return true;
    }

    return Release();
}

MediaState GstPlayer::get_state() {
    return state_;
}

bool GstPlayer::Init() {
    std::string description;

    // Initialize gstreamer
    gst_init(NULL, NULL);

    // Create pipeline
    description = std::string("filesrc location=") + file_path_ + std::string(" ! decodebin ! videoconvert ! ") + sink_ + std::string(" name=videosink");
    if (!sync_) {
        description += std::string(" sync=false");
    }
    pipeline_ = gst_parse_launch(description.c_str(), NULL);

    // Get bus
    bus_ = gst_element_get_bus(pipeline_);

    // Create main loop
    main_loop_ = g_main_loop_new(NULL, FALSE);

    // Get sink to set display window
    GstElement *sink = gst_bin_get_by_name(GST_BIN (pipeline_), "videosink");
    if (sink && xwinid_) {
        printf("-- GST: Set overlay, wID = %lu\n", xwinid_);
        gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid_);
    }

    // Add watch
    gst_bus_add_signal_watch (bus_);

    // Connect signal
    g_signal_connect(bus_, "message", G_CALLBACK (bus_callback), this);

    // Set pipeline ready to play.
    gst_element_set_state(pipeline_, GST_STATE_READY);

    state_ = STATE_READY;

    return true;
}

bool GstPlayer::Release() {
    if (state_ == STATE_NULL) {
        return true;
    }
    g_main_loop_unref (main_loop_);
    gst_object_unref (bus_);
    gst_element_set_state (pipeline_, GST_STATE_NULL);
    gst_object_unref (pipeline_);

    state_ = STATE_NULL;

    return true;
}

gboolean GstPlayer::bus_callback(GstBus* bus, GstMessage* msg, gpointer data) {
    GstPlayer* media = (GstPlayer*)data;

    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
        printf("-- MSG: ERROR\n");
        media->stop();
        break;
    }
    case GST_MESSAGE_EOS:
        printf("-- MSG: EOS\n");
        media->stop();
        break;
    default:
        /* Unhandled message */
        break;
    }
}
