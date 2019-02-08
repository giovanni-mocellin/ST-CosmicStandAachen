#include "DataStructures.h"

float WirePos (float channel, char layer_type)
{
    float xpos = 0;
    float x0 = 1.33; // cm , first channel in first module from left side
    
    if (layer_type == 'A') channel = channel - 1;
    if (layer_type == 'B') channel = 96 - channel;
    
    int module = int(float(channel)/8.0); // module from 0 to 11
    int channel_in_module = int(channel) % 8;
    
    xpos = x0 + 16.66 * module + 2.0 * channel_in_module;
    
    return xpos;
}

float HStripPos (float channel, char layer_type)
{
    float ypos = 0;
    
    if (layer_type == 'A' || layer_type == 'B')
    {
        ypos = 2 * channel - 1.1; // 2 : interstrip pitch is 2 cm & -1.0 : channel 1 -> mean position @ 1 cm & -0.1 : mean position of strip 1 is 0.9 and not 1.0 cm (strip is 1.8 cm wide)
    }
    
    return ypos;
}

mqDStrip DStripPos (float channel, char layer_type)
{
    mqDStrip dpos;
    
    if (layer_type == 1) dpos.m = 1/sqrt(3);
    if (layer_type == 2) dpos.m = - 1/sqrt(3);
    
    if (layer_type == 'A')
    {
        dpos.q = 19.9 + 4 * (96 - channel) - 199.92 * dpos.m;
    }
    if (layer_type == 'B')
    {
        dpos.q = 39.9 + 4 * (96 - channel);
    }
    
    return dpos;
}
