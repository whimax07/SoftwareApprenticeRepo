# Create a RingBuffer class.
#
# A Ring Buffer or Circular buffer or Circular queue all refer to ruffly the same thing.
# A fixed size buffer that you can add to and remove from in a first in first out manner.
# I.E. you add to the front of the buffer and remove from the back.
#
# Example:
# ringBuffer = {1, 2, 3, 4}                           // size = 4
# Add 5 to the buffer: {1, 2, 3, 4, 5}                // size = 5
# Remove an element from the buffer: {2, 3, 4, 5}     // size = 4
#
# RingBuffers are normally implemented with two pointer a head and tail. Where
# elements are added to the head and removed from the tail (or vice versa).
#
# The task is to create a libray (vocabulary) style class with doc string on
# each public method and tests. The API should include:
# * PUSH to add an element to the buffer.
# * PEAK to look at the oldest element in the buffer.
# * POP to return the oldest element and remove it from the queue.
# * PRINT to pretty print the current buffer.


