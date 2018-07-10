#ifndef SRC_GST_PLAYER_H
#define SRC_GST_PLAYER_H

#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>
#include "GstPlayerMessage.h"
enum MediaState {
  STATE_NULL,
  STATE_READY,
  STATE_PLAYING,
  STATE_PAUSED,
};

class CGstPlayer {
 public:
  CGstPlayer();
  CGstPlayer(const std::string &file_path, const std::string &sink, bool sync = true, guintptr winid = 0);
  ~CGstPlayer();

  bool open(const std::string &file_path, const std::string &sink, bool sync = true, guintptr winid = 0);
  bool play();
  bool pause();
  bool stop();
  bool setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
  MediaState get_state();

  void RegisterMessageCallback(GstPlayerMessage* callback);
  GstPlayerMessage* GetMessageCallBack();
private:

  bool Init();
  bool Release();
  static gboolean Gst_Bus_Callback(GstBus *bus, GstMessage *msg, gpointer data);

 private:
  GstPlayerMessage *m_pMessageCallBack;
  GstElement *m_pPipeline;
  GstBus *m_pBus;

  double m_dVolume;

  std::string m_filepath;
  std::string n_sinkname;
  bool m_bSync;
  guintptr m_pWinid;
  MediaState m_state;
  unsigned int m_x_;
  unsigned int m_y_;
  unsigned int m_width_;
  unsigned int m_height_;


};

#endif // SRC_GST_PLAYER_H
