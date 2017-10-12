#ifndef SRC_GST_PLAYER_H
#define SRC_GST_PLAYER_H

#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>

enum MediaState
{
  STATE_NULL,
  STATE_READY,
  STATE_PLAYING,
  STATE_PAUSED,
};

class GstPlayer {
public:
  GstPlayer();
  GstPlayer(const std::string& file_path, const std::string& sink, bool sync = true, guintptr xwinid = 0);
  ~GstPlayer();

  bool open(const std::string& file_path, const std::string& sink, bool sync = true, guintptr xwinid = 0);
  bool play();
  bool pause();
  bool stop();
  MediaState get_state();
private:
  GMainLoop*  main_loop_;
  GstElement* pipeline_;
  GstBus* bus_;
  
  double volume_;

  std::string file_path_;
  std::string sink_;
  bool sync_;
  guintptr xwinid_;
  MediaState state_;

  bool Init();
  bool Release();
  static gboolean bus_callback(GstBus* bus, GstMessage* msg, gpointer data);
};

#endif // SRC_GST_PLAYER_H
