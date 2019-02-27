# Unpacker and track reconstruction SW

## Unpacker
- ZeroSuppression, merging the different chunk files for all the ROAs into a single one.
- Output is a root file with raw data in a TTree stucture, like: event by event: vector_of_channels_fired_in_ROA_1 | vector_of_channels_fired_in_ROA_2 | vector_of_channels_fired_in_ROA_3 ...

## RawToDigi
- Interpretation of the readout channels to detector physical channels
- Occupancy plots per layer and type (wire, strip, dstrip)
- Merging of the neighboring channels into a single one ("merged digis" - from now on "digis")
- Digis now need to be a combination of all the hits in the wires, strips and dstrips. Indeed, it is impossible here to see which one is confirmed by the diagonal strips in order to eliminate the fake aliases
- Output is a root file with digi in a TTree stucture, like: event by event: vectors_of_digis_in_layer_1 | vectors_of_digis_in_layer_2 | vectors_of_digis_in_layer_3 | vectors_of_digis_in_layer_4

## DigiToRecHits
- Mapping of the digis into a coordinate value:
  - X is tranversal to the wires, Y is along the wires and Z is the vertical coordinate, fixed by the ST layer position
  - Line where the diagonal strips fired. Since the slope is defined for layer type A,B (30°), the diagonal hit can be represented by the intercept only
- Comparison between the 2D hit and the diagonal hit, to check if confirmed or not. If > two hits in the same layer, keep only the confirmed ones. If only one hit, even if it is not confirmed, keep it
- Output is a file that event by event gives the recHits of the four layers in (x,y,z,confirmation_by_dstrip) coordinates: again TTree like the one for digis ( lay1 | lay2 | lay3 | lay4 )

## Track reconstruction
- Reads the value of the recHits and fits the tracks event by event in the 2 planes (x,z) and (y,z)
- If multiple hits are found in one layer, the program fits all the combinations and selects the best track for the event (noise rejection) with lowest chi^2 (but not 0!!!)
- Output is a TTree with "used" recHits and tracks event by event. Track structure (mx,qx,chi2x,my,qy,chi2y)
