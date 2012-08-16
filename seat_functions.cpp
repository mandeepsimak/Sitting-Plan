#include "seat_classes.h"

// Reading room deatils from I/P file
void details :: room_details()
{
	infile.open(input_file);
	infile>>t_rooms;
	for(i=0; i<t_rooms; i++)
	{
		infile>>room_no[i]>>rows[i]>>cols[i];
	}
}

// Reading branch deatils from I/P file
void details :: rollno_details()
{
	infile>>total_branches;
	for(i=0; i<total_branches; i++)
	{
		infile>>branches[i]>>total_rno[i];//start_roll[i]>>end_roll[i];
		for(j=0; j<total_rno[i]; j++)
			infile>>rollno[i][j];
	}
}

// Definition of static variables.
int seat_planner :: nxt_branch;
int seat_planner :: nxt_room;

// Exam Details
void seat_planner::exam_details()
{
	//cout<<"\n1. Enter the Name of the exam: ";
	getline(cin, exam_name, '\n');
	cout<<"\n1. Enter the Name of the exam: ";
	getline(cin, exam_name, '\n');
	cout<<"\n2. Enter Date of the exam (eg 13-03-2012): ";
	getline(cin, exam_date, '\n');
	cout<<"\n3. Timing (eg 12:00pm  2:00pm): "; 
	getline(cin, exam_time, '\n');
}

// To display exam deatils
void seat_planner::exam_display()
{
	//outfile.open("seatplan.out");//, ios::app);
	outfile<<"\n\n\t\t\t"<<exam_name<<"\n\n\t\tDate:		"
		<<exam_date<<"\n\tTimings:	"<<exam_time;//<<"  to  "<<end_time;
}

void seat_planner :: get_details()
{
	room_details();
	rollno_details();
	infile.close();
}

void seat_planner :: set_room()	// Setting room deatils 
{
	if(nxt_room<t_rooms)				
	{
		row = rows[nxt_room];	// Rows of room
		col = cols[nxt_room];	// Columns of room
		exam_room = room_no[nxt_room];	// Room name		
		nxt_room++;	// Next room
	}
}

void seat_planner :: seatAB()
{
	if(nxt_branch == 0)
	{
		for(i=0; i<total_rno[nxt_branch]; i++)
		{
			seatA[i] = rollno[nxt_branch][i];
		}
		totalA = total_rno[nxt_branch];
		nxt_branch++;
		for(i=0; i<total_rno[nxt_branch]; i++)
		{
			seatB[i] = rollno[nxt_branch][i];
		}
		totalB = total_rno[nxt_branch];
		nxt_branch++;
	}
	
	else if(nxt_branch < total_branches)
	{
		if(m >= totalA)
		{
			for(i=0; i<total_rno[nxt_branch]; i++)
			{
				seatA[i] = rollno[nxt_branch][i];
			}
			totalA = total_rno[nxt_branch];
			m=0;
			nxt_branch++;
		}
		
		if(n >= totalB)
		{
			for(i=0; i<total_rno[nxt_branch]; i++)
			{
				seatB[i] = rollno[nxt_branch][i];
			}
			totalB = total_rno[nxt_branch];
			n=0;
			nxt_branch++;
		}
	}
	else //if(nxt_branch >= total_branches)
	{
		if(m >= totalA)
		{
			m=0;totalA=0;
			seatA[m] = 0;
		}
		if(n >= totalB)
		{
			n=0;totalB=0;
			seatB[n] = 0;
		}
	}
}

void seat_planner :: seat_plan()	// Allocate seats
{
	//set_branch();	// Calling set_branch() 
	seatAB();
	m = 0; n = 0;
	
	for(int rm = 0; rm<t_rooms; rm++)
	{
		set_room();	// Call to set_room() member function
		
		for(x=0; x<col; x++)		// For number of columns in a room	
		{
			for(y=0; y<row; y++)	// For number of rows in a room
			{
				seatAB();
				//set_rollno();       // Call to set_rollno() function
				if(y%2==0)
				{
					seat[rm][x][y] = seatA[m];	//start_roll1;	// seat allocation
					m++;	//start_roll1++;
				}
				else
				{
					seat[rm][x][y] = seatB[n];	//start_roll2;
					n++;	//start_roll2++;
				}
			}
			
		}
	}
	/*if(start_roll1 < end_roll1)        
	{
		fill_space(start_roll1,  end_roll1);
	}
	if(start_roll2 < end_roll2)
	{
		fill_space(start_roll2,  end_roll2);	
	}*/	
}

void seat_planner :: output()	// To display seat plan
{
	
	outfile.open("seatplan.out");//, ios::app);
		
	for(int a=0;a<t_rooms;a++)
	{
		sum=0;
		count_rollno();
		exam_display();
		outfile<<"\n\n\t\t Room No: "<<room_no[a]<<"\n\n";
		for(x=0; x<rows[a]; x++)
		{										
			for(y=0; y<cols[a]; y++)
			{
				outfile<<branch(seat[a][y][x])<<seat[a][y][x]<<"\t";
			}
			outfile<<"\n";
		}
	
		outfile<<"\n";
		for(i=0; i<total_branches; i++)
		{
			if(count[i] != 0)
			{
				outfile<<branches[i]<<":\t"<<count[i];
			}
			if(start_rno[i] != 37657 && end_rno[i] !=0)
				outfile<<"\tStart: "<<start_rno[i]<<"\t End: "<<end_rno[i]<<endl;
		}
		outfile<<"Total:\t"<<sum;
	}
	
	outfile.close();	
}

void seat_planner :: valid()
{
	int students=0, seats=0;
	max_rno = 0;
	char choice;

	for(x=0; x<total_branches; x++)
	{
		students += total_rno[x];
	}
	for(x=0; x<t_rooms; x++)
	{
		seats += (rows[x] * cols[x]);
	}

	if(students > seats)
	{
		system("clear");
		cout<<"\nThis strategy is not applicable because of less seats."
			<<endl<<"Total Seats: "<<seats<<endl
			<<"Total students: "<<students<<endl
			<<"More Seats Required: "<<(students-seats)<<endl
			<<"Please add more rooms in input file."<<endl;
	}
	else if(seats > students || seats == students)
	{
		system("clear");
		cout<<"\n Strategy - 1"
			<<endl<<"Total Seats: "<<seats<<endl
			<<"Total students: "<<students<<endl;
		int d = max_rno / 18;
		int r = max_rno % 18;
		if(d > t_rooms)
		{
			cout<<"This Strategy is not appicaple."<<endl
				<<"Rooms required for max. class rollno: "<<d<<endl
				<<"Add more rooms in input file to complete this stretegy"
				<<endl;
		}
		else
		{
			cout<<"\nStrategy applicable. Press 'Y' to continue."<<endl;
			cin>>choice;
		
			switch(choice)
			{
				case 'Y':
					exam_details();
					//report_choice();
					seat_plan();	// Call to seat_plan() function
					cout<<"\n Check seatplan.out file for seat plan."<<endl;
					break;
			
				default:
					cout<<"\nWrong Choice"<<endl;
					break;
			}
		}

	}
}

string seat_planner :: branch(int rno)
{
	string brnch;
	for(i=0; i<total_branches; i++)
	{
		for(j=0; j<total_rno[i]; j++)
		{
			if(rno==rollno[i][j])//start_roll[i] && rno<=end_roll[i])
			{
				brnch = branches[i];
				brnch.append("-");
				count[i]++;// = count[i] + 1;
				sum += 1;
				if(rno < start_rno[i])
					start_rno[i] = rno;
				if(rno > end_rno[i])
					end_rno[i] = rno;
				break;
			}
			
		}
	}
	return brnch;
}


void seat_planner::count_rollno()
{
	for(x=0;x<total_branches;x++)
	{
		count[x]=0;
		start_rno[x] = 37657;
		end_rno[x] = 0;
		if(total_rno[x]>max_rno)
			max_rno = total_rno[x];
	}
}


void seat_planner :: report_choice()
{
	
	do 
	{
		system("clear");
		cout<<"\n1. Enter 1 to generate the report Room-wise"
		<<"\n2. Enter 2 to generate the Report Branch-wise\n"
		<<"3. Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
			cout<<"\n you entered 1";
			break;
		
			case 2:
			cout<<"\nyou entered 2";		
			break;
						
			default:
			cout<<"Wrong Choice!!!!! Enter your choice again";
		}
	} while(choice!=1 && choice!=2);
}

//used to fill the remaining seats.
void seat_planner :: fill_space(int start_roll, int end_roll)
{
	for(int r=0;r<t_rooms;r++)
	{
		for(x=0;x<cols[r];x++)
		{
			for(y=0;y<rows[r];y++)
			{
				if( seat[r][x][y] == 0 && start_roll <= end_roll)
				{

					seat[r][x][y]=start_roll;
					start_roll++;
				}
			}
		}		
	}
			
}

