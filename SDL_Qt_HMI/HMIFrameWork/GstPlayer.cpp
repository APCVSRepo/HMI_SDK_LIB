#include <stdio.h>
#include "GstPlayer.h"
#include "HMIFrameWork/log_interface.h"
CGstPlayer::CGstPlayer()
  : m_pMessageCallBack(0)
  , m_state(STATE_NULL)
  , m_x_(0)
  , m_y_(0)
  , m_width_(0)
  , m_height_(0) {
}

CGstPlayer::CGstPlayer(const std::string &file_path, const std::string &sink, bool sync, guintptr winid)
  : m_filepath(file_path)
  , n_sinkname(sink)
  , m_bSync(sync)
  , m_pWinid(winid)
  , m_state(STATE_NULL)
  , m_x_(0)
  , m_y_(0)
  , m_width_(0)
  , m_height_(0) {
  Init();
}

CGstPlayer::~CGstPlayer() {
  if (m_state != STATE_READY) {
    stop();
  }

  Release();
}

bool CGstPlayer::open(const std::string &file_path, const std::string &sink, bool sync, guintptr winid) {

  if (m_state != STATE_NULL) return false;

  m_filepath = file_path;
  n_sinkname = sink;
  m_bSync = sync;
  m_pWinid = winid;

  return Init();
}

bool CGstPlayer::play() {
  if (m_state == STATE_PLAYING) {
    return true;
  } else if (STATE_NULL == m_state) {
    Init();
  }

  GstStateChangeReturn ret = gst_element_set_state(m_pPipeline, GST_STATE_PLAYING);
  if (GST_STATE_CHANGE_FAILURE != ret) {
    printf("-- GST: playing.\n");
    m_state = STATE_PLAYING;
    return true;
  } else {
    printf("-- GST: Failed to play.\n");
    Release();
  }

  return false;
}

bool CGstPlayer::pause() {
  if (m_state != STATE_PLAYING) {
    printf("-- GST: Is not playing, can not pause.\n");
    return false;
  }

  GstStateChangeReturn ret = gst_element_set_state(m_pPipeline, GST_STATE_PAUSED);
  if (GST_STATE_CHANGE_FAILURE != ret) {
    printf("-- GST: paused.\n");
    m_state = STATE_PAUSED;
    return true;
  } else {
    printf("-- GST: Failed to pause.\n");
  }

  return false;
}

bool CGstPlayer::stop() {
  if (STATE_NULL == m_state ) {
    return true;
  }

  return Release();
}

bool CGstPlayer::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  m_x_ = x;
  m_y_ = y;
  m_width_ = width;
  m_height_ = height;

  return true;
}

MediaState CGstPlayer::get_state() {
    return m_state;
}

void CGstPlayer::RegisterMessageCallback(GstPlayerMessage *callback)
{
    m_pMessageCallBack = callback;
}

GstPlayerMessage* CGstPlayer::GetMessageCallBack()
{
    return m_pMessageCallBack;
}

bool CGstPlayer::Init() {
  std::string description;

  // Initialize gstreamer
  gst_init(NULL, NULL);

  // Create pipeline
  description = std::string("filesrc location=") + m_filepath + std::string(" ! decodebin ! videoconvert ! ") + n_sinkname + std::string(" name=videosink");
  if (!m_bSync) {
    description += std::string(" sync=false");
  }
  m_pPipeline = gst_parse_launch(description.c_str(), NULL);
  // Get bus
  m_pBus = gst_element_get_bus(m_pPipeline);

  // Get sink to set display window
  GstElement *sink = gst_bin_get_by_name(GST_BIN (m_pPipeline), "videosink");
  if (sink && m_pWinid) {
#ifdef ARCH_X86
    printf("-- GST: Set overlay, wID = %lu\n", m_pWinid);
#elif ARCH_ARMHF
    printf("-- GST: Set overlay, wID = %u\n", m_pWinid);
#endif
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink), m_pWinid);
  }

  // Add watch
  gst_bus_add_signal_watch (m_pBus);

  // Connect signal
  g_signal_connect(m_pBus, "message", G_CALLBACK (Gst_Bus_Callback), this);

  // Set pipeline ready to play.
  gst_element_set_state(m_pPipeline, GST_STATE_READY);

  m_state = STATE_READY;

  if(m_pMessageCallBack)
  {
      m_pMessageCallBack->OnGstPlayerStatus(eGstPlayer_Ready);
  }

  return true;
}

bool CGstPlayer::Release() {
  if (STATE_NULL == m_state) {
    return true;
  }
  gst_object_unref(m_pBus);
  gst_element_set_state (m_pPipeline, GST_STATE_NULL);
  gst_object_unref(m_pPipeline);

  m_state = STATE_NULL;
  if(m_pMessageCallBack)
  {
      m_pMessageCallBack->OnGstPlayerStatus(eGstPlayer_NULL);
  }
  return true;
}

gboolean CGstPlayer::Gst_Bus_Callback(GstBus *bus, GstMessage *msg, gpointer data) {
  CGstPlayer *player = (CGstPlayer *)data;

  bus = bus; // Avoid warning: -Wunused-parameter
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
      printf("-- MSG: ERROR\n");
      player->stop();
      if(player->GetMessageCallBack())
      {
          player->GetMessageCallBack()->OnGstPlayerStatus(eGstPlayer_Error);
      }
      break;
    }
    case GST_MESSAGE_EOS:
      INFO("-- MSG: EOS");
      player->stop();
      if(player->GetMessageCallBack())
      {
          player->GetMessageCallBack()->OnGstPlayerStatus(eGstPlayer_Finish);
      }
      break;
    default:
      /* Unhandled message */
      break;
  }
  return true;
}
