# Final_Project_OSCP_Zuzanna_Buchnajzer


 As a final project, I chose a museum problem in which I synchronized the entrances and exits of visitors to rooms A and B.

## Implementation of the museum and visitors
For this, I used multithreading to make the whole process more natural. 

- threads: <0 to n)
   - Each of the n threads created at the beginning of the program, reflects one museum visitor. 
  
- semaphores: sem1, sem2, sem3
   - The created semaphores reflect the possible number of free space in each room, so when initializing them, I set their initial value to the possible maximum number for each room.
  
- mutexes: m1,m3
  - The mutexes created are used to make sure that not many people come through the door at once. Only exit (m3) is independent of the others because it does not harm anyone.
  
- room structures: A and B
  - Each structure has two variables `wantin` - telling about the wish of the selected visitor to enter the room, or `wantout` - telling about the wish to leave the room the structure belongs to. However, for the sake of clarity, I will describe the individual variables for room A and B, since A.wantin is not related to B.wantout, which may not be obvious.
    - room A: wantin- number of people outside the museum wanting to enter == not yet visited the museum.
wantout- number of visitors who want to leave the museum == visited as much museum as they wanted
    - room B: wantin- number of visitors who are in room A and want to visit room B.
wantout- number of visitors who want to leave room B.

  - capacity of room A and B
    - occupied capacity of room A= A.wantout+B.wantin and max value is max1.
    - occupied capacity of room B= B.wantout, and max value is max2.

## Visit plan
Each visitor, upon entering room A, decides (draws in 50rd line) whether he wants to visit room B (53rd line) or leaves the museum (jumps to 85th line). 

## Possibility of deadlock
However, I noticed that if all programs visit the entire museum, deadlock can easily occur. To prevent this, before going to the museum, the program checks for deadlock, which is the point where everyone in room A is waiting to go to room B, and everyone in room B, is waiting to go back to room A. 


  
