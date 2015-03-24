
- Compile and Execute C++ Online (GNU GCC version 4.8.1)
Help About Web Editors  Home
Command Line Arguments: 	  		STDIN Input: 	  	
Result
Download Files
Multiple Files

    main.cpp
    input.txt

Compile & Execute

36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
              distance = (xValue * xValue) + (yValue * yValue);
              if(distance <= 1.0)
                 ++pointsIn;
           }
           pi = 4.0 * pointsInTotal/(4 * totalpoints);
    }
    return param;
}
int main()
{
    srand(time(NULL));
    pthread_t handles[N];
    Info info[N];
    // start the threads
    for (size_t i = 0; i != 4; ++i)
        pthread_create(&handles[i], NULL, func, &info[i]);
    // wait for the threads to complete
    for (size_t i = 0; i != 4; ++i)
        pthread_join(handles[i], NULL);
    // process the reply
    for (size_t i = 0; i != 4; ++i)
        std::cout << "value[" << i << "] = " << info[i].pi << std::endl;
    return 0;
}

