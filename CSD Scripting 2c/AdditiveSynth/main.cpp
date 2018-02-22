#include <iostream>
#include <soundio/soundio.h>

#include "SineWave.h"

using namespace std;

static void write_callback(struct SoundIoOutStream* out, int frame_count_min, int frame_count_max)
{

}

int main()
{
  SineWave sine = SineWave(440);
  cout << "Sine wave: ";
  cout << "freq: " << sine.getFrequency() << ", ";
  cout << "amp: " << sine.getAmplitude() << ", ";
  cout << "phase offset: " << sine.getPhaseOffset() << endl;

  int err;
  struct SoundIo* soundio = soundio_create();
  if (!soundio)
  {
    cerr << "out of memory" << endl;
    return 1;
  }

  if ((err = soundio_connect(soundio)))
  {
    cerr << "error connecting: " << soundio_strerror(err) << endl;
    return 1;
  }

  soundio_flush_events(soundio);

  int default_out_device_index = soundio_default_output_device_index(soundio);
  if (default_out_device_index < 0)
  {
    cerr << "no output device found" <<endl;
    return 1;
  }

  struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
  if (!device)
  {
    cerr << "out of memory" << endl;
    return 1;
  }

  cout << "Output device: " << device->name << endl;

  struct SoundIoOutStream *outstream = soundio_outstream_create(device);
  if (!outstream)
  {
    cerr << "out of memory" << endl;
    return 1;
  }
  outstream->format = SoundIoFormatFloat32NE;
  outstream->write_callback = write_callback;

  if ((err = soundio_outstream_open(outstream))) {
    cerr << "unable to open device: " << soundio_strerror(err) << endl;
    return 1;
  }

  if (outstream->layout_error)
    cerr << "unable to set channel layout: " << soundio_strerror(outstream->layout_error) << endl;

  if ((err = soundio_outstream_start(outstream))) {
    cerr << "unable to start device: " << soundio_strerror(err) << endl;
    return 1;
  }

  for (;;)
    soundio_wait_events(soundio);

  soundio_outstream_destroy(outstream);
  soundio_device_unref(device);
  soundio_destroy(soundio);

  return 0;
}
