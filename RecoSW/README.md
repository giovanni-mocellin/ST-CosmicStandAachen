# Unpacker and track reconstruction SW

## Unpacker
Steps:
- ZeroSuppression, merging the different chunk files for all the ROAs into a single one (¿skipping chunk zero?)
  - It can be a root file with raw data in a tree stucture, like: event by event: vector_of_channels_fired_in_ROA_1 vector_of_channels_fired_in_ROA_2 vector_of_channels_fired_in_ROA_3 ...
  - Or a simple .txt file, like:
    Event 0
    ROA1 1 32 57
    ROA2 4 5
    ROA3 ...
    ...
    Event 1
    ...
- Interpretation of the channels of the boards. This includes 4 steps:
  - Merging of the neighboring channels into a single one (need to specify cluster size to get the error on the recHit)
  - Mapping of the merged channel into a coordinate value:
    - X is tranversal to the wires, Y is along the wires and Z is the vertical coordinate, fixed by the ST layer position
    - Line where the diagonal strips fired. Since the slope is defined for layer type A,B (30°), the diagonal hit can be represented by the intercept only
  - Comparison between the 2D hit and the diagonal hit, to check if confirmed or not (it should be... within the cluster size!)
  -  Creating a final file that event by event gives the recHits of the four layers in X,Y,Z coordinates

## Track recontruction
The code is based on ROOT: reads the value of the recHits 
