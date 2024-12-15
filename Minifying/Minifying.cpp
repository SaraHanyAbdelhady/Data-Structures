#include <bits/stdc++.h>
 using namespace std;
 void Minifying(ifstream &input_file, ofstream &output_file)
 {
    bool in_comment=false,in_tag=false,between_tags=false,notext=false;
    int notext_counter=0;
    string line;
    while (getline(input_file, line))
    {
        //remove indentation from extracted line
        int start = 0; //initialize variable start with 0
        //if start didnt reach end of string and there is space or tab or new line or carriage return so skip that char
        while (start < line.size() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\n' || line[start] == '\r'))
            start++;
        int end = line.size(); //initialize end by size of string
        //start from end and as long as you don't reach start so if you detect space or new line or carriage return or tab skip that char by decrementing end
        while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t' || line[end - 1] == '\n' || line[end - 1] == '\r'))
            end--;
        //update the string with the new start and end
        line = line.substr(start, end - start);
        //loop on every character in the line
        for(int i=0;i<line.length();i++)
        {
            //switch on that character
            switch(line[i])
            {
                case'<':
                    if(between_tags)
                    {
                        //if you were already between tags and then char became <
                        //so you became inside tag not between tag
                        between_tags=false;
                        in_tag=true;
                    }
                    else
                        in_tag=true; //if you weren't between tags so you only became inside tags and no need to make between tags to false
                    //if you detect <!-- so you are inside a comment
                    if(i+3<line.length()&&line[i+1]=='!'&&line[i+2]=='-'&&line[i+3]=='-')
                    {
                        in_comment=true;
                        //skip <!-- characters
                        i+=2;
                        continue;
                    }
                    break;
                case'>':
                    if(in_tag)
                    {
                        //if you were already in tag and then character became > so you are out of the tags and are now between tags
                        in_tag=false;
                        between_tags=true;
                    }
                    break;
                case '-':
                    //if you are inside comment and you detect --> so thats end of comment
                    if(in_comment&&i+2<line.length()&&line[i+1]=='-'&&line[i+2]=='>')
                    {
                        in_comment=false;
                        //skip -->
                        i+=3;
                        continue;
                    }
                    break;
            }
            //skip comments
            if(in_comment)
                continue;
            output_file<<line[i];
        }
    }
 }
 int main() {
    ifstream file("input_file.xml");
    ofstream file2("Minified.xml");
    Minifying(file, file2);
    file.close();
    file2.close();
    cout << "File minified successfully";
    return 0;
 }
