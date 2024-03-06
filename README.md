# ReadFilter
This library contains functions to filter analogRead values using normal average and moving window average methods, with option to remove outliers for robust readings.

## Using the library
Download these files as a zip file and extract the contents to a folder named 'ReadFilter' inside the Arduino -> libraries folder, along with other Arduino libraries. 
Include this library in your code as:

              #include<ReadFilter.h>
## Initialising Filter Object
ReadFilter object has to be created to invoke the filter functions. The following parameters can be passed during filter creation to customize the filter.

- **int w**     -> Measurement window size (_by default: 10_, _max: 20_) 
- **float ml**  -> value corresponding to analogRead value of 0 (for mapping, _by default: 0_)
- **float mh**  -> value corresponding to analogRead value of 1023 (for mapping,  _by default: 1023_)
- **bool outr** -> Boolean parameter to activate outlier rejection (_by default: false_)
- **float n**   -> To define threshold for outlier rejection (_by default: 1_)
- **int d**     -> Delay (pause) in micro seconds after each analogRead by the filter (_by default: 100_)

The paramters can be passed while creaing the filer object : 

            #include<ReadFilter.h>
            ReadFilter rf(15,0,180,false,1,100);
            void setup(){// put your setup code here, to run once:
            }
            void loop(){// put your main code here, to run repeatedly:
            }

or can be done in the later part of the code by calling the _ReadFilter()_ constructor, passing the desired paramters.

            #include<ReadFilter.h>
            ReadFilter rf;
            void setup(){// put your setup code here, to run once:
            rf = ReadFilter(15,0,180,false,1,100);
            }
            void loop(){// put your main code here, to run repeatedly:
            }

In both the above cases, a ReadFilter object rf is created that uses a measurement window of 15 and returns a filtered value that is mapped from 0 to 180.

## Simple Average
Simple average of readings within the measurement window can be computed using the _.avg(int p)_ method of the filter, where _p_ is the analogRead pin number. This method returns a single average value for _w_ readings that is taken by the filter, with a time delay of _d_ after each reading. 
  
          avg_rdng = rf.avg(A0);

## Moving Window Average
_.mvgavg(int p)_ computes the moving window average by averaging out past _w_ readings. Returns a filtered value for each reading taken by the filter through analogRead. Hence, preferable for high measurement rate.

          mvg_avg_rdng = rf.mvgavg(A0);
          
## Outlier Rejection
The outlier rejection is done by eliminating the readings in the window that are not in the range [mean-_n_*sigma,mean+_n_*sigma ], where mean is the average of the readings in the window and sigma is the standard deviation. This feature greatly helps to remove noises that are more common due to loose wire contacts in arduino projects.

## Clear Filter
The _.mvgavg()_ method utilizes past (_w-1_) readings that are stored inside the filter object to return a filtered value for the current reading. Hence, it is necessary to clear the filter using the _.clr()_ method, before using the same filter object for reading different pin or for the same pin at a different point in time, to avoid erroneous estimates out of junk value. 

          rf.clr();

Multiple filter objects can be created to filter readings from different pins parallely. 

          ReadFilter f1(15,0,180,false,1,100), f2(15,0,180,false,1,100);
          a = f1.mvgavg(A0);
          b = f2.mvgavg(A1);

## Remarks
Various factors such as loose wire contacts, sensor inaccuracies, machine vibration etc, can contribute to noisy readings. Use of these unfiltered readings directly transfers this input noise to the output response, resulting in undesired robot behaviour. Hence, the use of filters is necessary for the development of robust mechatronic systems. This library offers basic filtering tools that would satisfy the requirement of most low to mid-level robotic and mechatronic systems.      

          
