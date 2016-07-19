# GE1111-Facial-Recognition
Final Facial Recognition project for NU GE1111

# Purpose
Reads in facial measurement data that can be obtained from photographs. The program works by finding the distance between 5 measured points on the face (eq. 1) – the ears, eyes, and nose – then adding the squares of the distances together to obtain an individual’s ‘score’ (eq. 2).  It then finds the top four smallest scores (thus the closest matches) and returns x-y plots of the facial structure along with names and scores.  This particular program also features the ability to print out in a text file the names of the top four suspects, with their respective scores, in increasing order.

#Formulas
distance = sqrt((x1-x2)^2+(y1-y2)^2)
Score = sum(((knownDistance(a))-(suspectDistace(a)))^2)

# Use
To use the program, one should begin with two input text files: the first structured like a database file (such as facedata.txt) and a suspect file for comparison (such as suspect_1.txt).  Open and run the C++ file first, and enter the full name of the suspect file when prompted (eg. ‘suspect_1.txt’) then press enter.  The program will have applied the analysis formulas and outputted several data files, four for use by MATLAB for graphing (results_names, results_scores, results_xvals, results_yvals) and a fifth text file containing the names and scores of the top 4 matched suspects, in order [Extra Credit] (scoresuspect.txt).  The user can then close the C++ file and open the MATLAB file, taking care to open the main program and not the function file.  Upon running the MATLAB program, a single figure containing the four graphs of the top four suspects will be outputted to a window.
