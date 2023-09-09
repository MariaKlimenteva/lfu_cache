# LFU-Cache
This is an implementation of **LFU caching** (*least frequently used*). LFU is a type of cache algorithm used to manage memory within a computer. The standard characteristics of this method involve the system keeping track of the number of times a block referenced in memory. When the cache is full and requires more room the system will purge the item with the lowest reference frequency.

- ***Ideal LFU***: there is a counter for each item in the catalogue
- ***Practical LFU***: there is a counter for the items stored in cache. The counter is forgotten if the item is evicted.

#### Testing system
I try the Google testing system, using it to check the value of outliers, where the data is taken from the file.
#### About ideal cache algorithm
An **ideal cache** is when we know exactly how many times and when we will need to put a certain element in the cache. 
I am creating a special map (*duplicate_elements*) that contains pairs of the element value and a vector from the indexes when the desired element is encountered. By comparing these indexes, I can determine which element I can replace in order to achieve the greatest number of hits.