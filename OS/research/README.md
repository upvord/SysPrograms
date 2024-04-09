# Project Title: Process Synchronization Using Semaphores

## Overview
This project demonstrates the synchronization of three separate processes accessing a shared memory space using semaphores. The goal is to ensure that each process accesses the shared resource without interfering with each other, thus avoiding data corruption.

### Implementing Process 1 (Capital A-Z Writer)
- **Step 1:** Implement process 1, which is responsible for writing capital letters A-Z to the shared memory. It is crucial to utilize semaphores to gain exclusive access to the memory while writing to ensure data integrity.
- **Step 2:** Once the writing operation is complete, process 1 should signal the next process. This signaling indicates that process 2 can start writing or process 3 can start reading, based on your synchronization design.

### Implementing Process 2 (Small a-z Writer)
- **Step 3:** Implement process 2, tasked with writing lowercase letters a-z to the shared memory. Similar to process 1, this process must use semaphores to secure exclusive access during its operation to prevent data mingling.
- **Step 4:** Upon completing its writing task, process 2 should signal that it's finished. This allows process 3 to begin reading or to continue the cycle, depending on the design of the synchronization mechanism.

### Implementing Process 3 (Reader and Dumper)
- **Step 5:** Process 3's role is to read the shared memory. It must synchronize with processes 1 and 2 to ensure that it reads only complete and consistent data, thereby verifying the integrity of the information.
- **Step 6:** After reading, process 3 should dump or display the information from the shared memory. This step is crucial for verifying that the data read is not mixed and follows the writing order of processes 1 and 2 correctly.

## Conclusion
Following these steps will ensure that the processes access the shared memory in an orderly and synchronized manner, using semaphores to manage the access control. This project aims to demonstrate the effectiveness of semaphores in process synchronization within the context of shared memory usage.


## Sample Output
--- Shared Memory Contents ---
a b c d e f g h i j k l m n o p q r s t u v w x y z
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
--- End of Shared Memory Contents ---


# Project Title: Process Synchronization Using Semaphores

## Expected Output
The expected output demonstrates that process 2 writes lowercase letters a-z followed by process 1 writing uppercase letters A-Z, without any mingling of data. Process 3 reads and dumps this data in the specified order.

--- Shared Memory Contents ---
a b c d e f g h i j k l m n o p q r s t u v w x y z
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
--- End of Shared Memory Contents ---


## Unexpected Outputs
Unexpected outputs indicate failures in synchronization among the processes, leading to mingled, missing, or disordered data.

### Example 1: Letters Are Mingled
--- Shared Memory Contents ---
a A b B c C d D e E f F g G h H i I j J k K l L m M n N o O p P q Q r R s S t T u U v V w W x X y Y z Z
--- End of Shared Memory Contents ---

This output shows mingled lowercase and uppercase letters, suggesting simultaneous or incorrect order of access.

### Example 2: Missing or Extra Letters
--- Shared Memory Contents ---
a b c d e f g h i j k l m n o p q r s t u v w x y z
A B D E F G H I J K L M N O P Q R S T U V W X Y Z
--- End of Shared Memory Contents ---

Here, the letter `C` is missing from the uppercase sequence, indicating a possible overwrite or incomplete operation.

### Example 3: Completely Out of Order
--- Shared Memory Contents ---
D E F G a b c d H I J K L M N O P Q R S T U V W X Y Z e f g h i j k l m n o p q r s t u v w x y z A B C
--- End of Shared Memory Contents ---

This shows a significant disorder, suggesting a failure in enforcing the correct operational order.

## Conclusion
The expected and unexpected outputs illustrate the critical importance of proper semaphore use and p
