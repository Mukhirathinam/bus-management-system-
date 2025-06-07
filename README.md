# bus-management-system-
Bus Reservation System (C Language)
Description
This project is a simple Console-based Bus Reservation System written in C, which allows users to:
- View available buses and their schedules
- Reserve tickets by choosing bus number and seat
- View reservation details using a unique customer ID
- Cancel booked tickets
- Display current seat status per bus
The system uses a Binary Search Tree (BST) to manage reservations and a 2D array to maintain seat
statuses.
Features
- Login system for basic user authentication
- Reservation module using unique Customer IDs (auto-generated)
- Binary Search Tree (BST) for efficient lookup
- Color-coded terminal output
- Seat display showing available/booked seats
- Ticket cost calculator based on bus number
Tech Stack
- Language: C
- Platform: Windows / DOS-based Terminal
- Header Files: <stdio.h>, <stdlib.h>, <string.h>, <conio.h>, <time.h>
How to Run
Compilation:
gcc bus_reservation.c -o bus_reservation
Execution:
./bus_reservation
Bus Reservation System (C Language)
Note: conio.h functions like getch() may not be supported on Linux. Use getchar() instead.
Login Credentials
- Username: user
- Password: team15
Sample Operations
1. Reserve Ticket: Choose bus number and seat. Generates unique Customer ID.
2. View Reservation: Enter Customer ID to view details.
3. Cancel Ticket: Enter Customer ID to cancel.
4. Display Seats: Show booked/empty seats.
5. Bus List: Show routes, times, charges.
To-Do / Improvements
- Add file I/O for persistent storage
- Replace goto statements with loops/functions
- Input validation for names and IDs
- Replace deprecated gets() with fgets()
License
This project is open-source and free for educational use.
