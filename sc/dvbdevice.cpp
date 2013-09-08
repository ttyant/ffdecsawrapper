/*
 * dvbdevice.c: The DVB device interface
 *
 * See the main source file 'vdr.c' for copyright information and
 * how to reach the author.
 *
 * $Id: dvbdevice.c 1.93 2004/06/19 09:33:42 kls Exp $
 */

#include "include/ffdecsawrapper/dvbdevice.h"
#include <errno.h>
#include <limits.h>
#include <libv4l1-videodev.h>
#include <linux/dvb/audio.h>
#include <linux/dvb/dmx.h>
#include <linux/dvb/frontend.h>
#include <linux/dvb/video.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define DO_REC_AND_PLAY_ON_PRIMARY_DEVICE 1
#define DO_MULTIPLE_RECORDINGS 1
//#define WAIT_FOR_LOCK_AFTER_TUNING 1

#define DEV_VIDEO         "/dev/video"
#define DEV_DVB_ADAPTER   "/dev/dvb/adapter"
#define DEV_DVB_OSD       "osd"
#define DEV_DVB_FRONTEND  "frontend"
#define DEV_DVB_DVR       "dvr"
#define DEV_DVB_DEMUX     "demux"
#define DEV_DVB_VIDEO     "video"
#define DEV_DVB_AUDIO     "audio"
#define DEV_DVB_CA        "ca"

// --- cDvbDevice ------------------------------------------------------------

int cDvbDevice::devVideoOffset = -1;
int DvbOpen(const char *Name, int n, int Mode, bool ReportError=false);
cDvbDevice::cDvbDevice(int n)
{
    //int camfd;
    fd_video = 0;
    cardIndex=n;
    //For ffdecsawrapper, we never use the ca device here!
    //camfd=DvbOpen("ca",cardIndex,O_RDWR|O_NONBLOCK);
    //if (camfd > 0)
    //{
    //    fd_video = 1;
    //    close(camfd);
    //}
    //else
    //    fd_video = 0;
    //printf("HW Decoder: %s\n", fd_video ? "Yes" : "No");
}

cDvbDevice::~cDvbDevice()
{
}

bool cDvbDevice::Probe(const char *FileName)
{
  return false;
}

bool cDvbDevice::Initialize(void)
{
  return true;
}

void cDvbDevice::MakePrimaryDevice(bool On)
{
}

bool cDvbDevice::HasDecoder(void) const
{
  return fd_video;
}

#include "include/ffdecsawrapper/plugin.h"
#define SC_NAME "sc"
#define SC_MAGIC { 0,'S','C',0xc4,0x5e,0xa1 }
#define OP_PROVIDES 0
#define OP_IGNORE   1

struct ScLink {
  char magic[6];
  short op;
  const cDevice *dev;
  unsigned short *caids;
  const cChannel *channel;
  int num;
  };

cSpuDecoder *cDvbDevice::GetSpuDecoder(void)
{
  return NULL;
}

void cDvbDevice::SetVideoFormat(bool VideoFormat16_9)
{
}

eVideoSystem cDvbDevice::GetVideoSystem(void)
{
  return vsNTSC;
}

//                            ptAudio        ptVideo        ptPcr        ptTeletext        ptDolby        ptOther
dmx_pes_type_t PesTypes[] = { DMX_PES_AUDIO, DMX_PES_VIDEO, DMX_PES_PCR, DMX_PES_TELETEXT, DMX_PES_OTHER, DMX_PES_OTHER };

bool cDvbDevice::SetPid(cPidHandle *Handle, int Type, bool On)
{
  return true;
}

int cDvbDevice::OpenFilter(u_short Pid, u_char Tid, u_char Mask)
{
  return -1;
}

bool cDvbDevice::ProvidesSource(int Source) const
{
  return true;
}

bool cDvbDevice::ProvidesTransponder(const cChannel *Channel) const
{
  return false;
}

bool cDvbDevice::ProvidesChannel(const cChannel *Channel, int Priority, bool *NeedsDetachReceivers) const
{
  bool result = false;
  return result;
}

bool cDvbDevice::SetChannelDevice(const cChannel *Channel, bool LiveView)
{
  return true;
}

bool cDvbDevice::HasLock(int TimeoutMs)
{
  return true;
}

void cDvbDevice::SetVolumeDevice(int Volume)
{
}

void cDvbDevice::SetAudioTrackDevice(eTrackType Type)
{
}

bool cDvbDevice::CanReplay(void) const
{
  return false;
}

bool cDvbDevice::SetPlayMode(ePlayMode PlayMode)
{
  return true;
}

int64_t cDvbDevice::GetSTC(void)
{
  return -1;
}

void cDvbDevice::TrickSpeed(int Speed)
{
}

void cDvbDevice::Clear(void)
{
}

void cDvbDevice::Play(void)
{
}

void cDvbDevice::Freeze(void)
{
}

void cDvbDevice::Mute(void)
{
}

void cDvbDevice::StillPicture(const uchar *Data, int Length)
{
}

bool cDvbDevice::Poll(cPoller &Poller, int TimeoutMs)
{
  return false;
}

bool cDvbDevice::Flush(int TimeoutMs)
{
  return true;
}

int cDvbDevice::PlayVideo(const uchar *Data, int Length)
{
  return -1;
}

int cDvbDevice::PlayAudio(const uchar *Data, int Length, uchar Id)
{
  return -1;
}

bool cDvbDevice::OpenDvr(void)
{
  return false;
}

void cDvbDevice::CloseDvr(void)
{
}

bool cDvbDevice::GetTSPacket(uchar *&Data)
{
  return false;
}

bool cDvbDevice::Ready(void)
{
  return true;
}

bool cDvbDevice::IsTunedToTransponder(const cChannel *Channel)
{
  return true;
}

bool cDvbDevice::HasCi(void)
{          
  return false;
}             

uchar *cDvbDevice::GrabImage(int &Size, bool Jpeg, int Quality, int SizeX, int SizeY)
{
  return NULL;
}

void cDvbDevice::SetVideoDisplayFormat(eVideoDisplayFormat VideoDisplayFormat)
{
}

int cDvbDevice::GetAudioChannelDevice(void)
{
  return 0;
}

void cDvbDevice::SetAudioChannelDevice(int AudioChannel)
{
}

void cDvbDevice::SetDigitalAudioDevice(bool On)
{
}

void cDvbDevice::SetTransferModeForDolbyDigital(int Mode)
{
}
