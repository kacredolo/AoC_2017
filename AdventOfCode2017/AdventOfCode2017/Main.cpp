/*
--------Part 1--------        --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
25   00:24:06    432      0   00:24:22    384      0
24   01:11:30    522      0   01:55:00    625      0
23   00:19:39    560      0   01:16:19    274      0
22   02:59:39   1187      0   04:17:23   1316      0
21   02:55:14    595      0   03:00:48    577      0
20   00:23:45    379      0   01:14:08    622      0
19   00:27:31    319      0   00:28:50    275      0
18   00:42:14    656      0   03:23:22    832      0
17   00:20:36    640      0   00:30:43    390      0
16   00:19:45    426      0   01:03:41    462      0
15   00:46:52   1116      0   00:52:28    983      0
14   01:43:35   1389      0   02:04:01    953      0
13   00:12:45    154      0   00:43:42    383      0
12   00:33:52   1023      0   00:36:40    811      0
11   00:17:53    355      0   00:22:50    338      0
10   00:19:01    255      0   00:45:46    345      0
9    00:14:10    256      0   00:16:27    232      0
8    00:16:29    526      0   00:18:05    505      0
7    00:39:15   1346      0   01:25:12    873      0
6    01:09:34   1912      0   01:14:15   1822      0
5    00:06:47    473      0   00:08:58    440      0
4    00:08:45    780      0   00:16:35    775      0
3    01:06:30   1106      0   01:53:42    908      0
2    00:15:33    947      0   00:21:48    692      0
1    22:01:20  18086      0   22:13:44  15055      0

Final Thoughts on this years : 
There were a lot more people this year. The leaderboard just wasn't worth chasing. 
Going fast typically ends with some bad code practices, halfway through this year I started using more object oriented approaches which was slower but more rewarding.
These are always fun but I think I liked last years problems more.

Overall Completion Stats for everyone at 9:36pm 12-24-07
https://adventofcode.com/2017/stats
Day  Part 2   Part 1    Stars
25   532      70		**
24   2692     41		****
23   3086     831		****
22   3942     112		*****
21   3714     72		*****
20   5057     513		******
19   5934     72		*******
18   5475     1398		*******
17   6870     461		********
16   7180     757		********
15   7958     211		*********
14   7095     650		********
13   8470     849		*********
12   9678     398		**********
11   10020    363		***********
10   10230    1132		************
9    12351    294		*************
8    14219    382		**************
7    12986    4004		****************
6    18197    825		******************
5    20841    1138		*********************
4    22408    2430		************************
3    19354    6792		*************************
2    31611    5512		**********************************
1    37081    7398		*****************************************
*/

#include <iostream>
#include "Challenge1.h"
#include "Challenge2.h"
#include "Challenge3.h"
#include "Challenge4.h"
#include "Challenge5.h"
#include "Challenge6.h"
#include "Challenge7.h"
#include "Challenge8.h"
#include "Challenge9.h"
#include "Challenge10.h"
#include "Challenge11.h"
#include "Challenge12.h"
#include "Challenge13.h"
#include "Challenge14.h"
#include "Challenge15.h"
#include "Challenge16.h"
#include "Challenge17.h"
#include "Challenge18.h"
#include "Challenge19.h"
#include "Challenge20.h"
#include "Challenge21.h"
#include "Challenge22.h"
#include "Challenge23.h"
#include "Challenge24.h"
#include "Challenge25.h"

using namespace std;

typedef void(*func)();
void main() {
	vector<func> Challenges = { 
		Challenge1, Challenge2, Challenge3, Challenge4, Challenge5,
		Challenge6, Challenge7, Challenge8, Challenge9, Challenge10,
		Challenge11, Challenge12, Challenge13, Challenge14, Challenge15,
		Challenge16, Challenge17, Challenge18, Challenge19, Challenge20,
		Challenge21, Challenge22, Challenge23, Challenge24, Challenge25
	};

	int selection;
	while (1) {
		do {
			cout << "Select a challenge 1-25 : ";
			cin >> selection;
			system("CLS");
		} while (selection <= 0 || selection > 25);
		time_t challengeTime = time(NULL);
		cout << "Running Challenge " << selection << endl;
		(*Challenges[selection-1])();
		cout << "Challenge " << selection << " took " << time(NULL) - challengeTime << " seconds."<<endl;
	}
}
