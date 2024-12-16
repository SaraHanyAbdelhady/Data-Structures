#include <bits/stdc++.h>
 using namespace std;
 //function to remove indentation
 void remove_indentation(string& line);
 //Minifying function
 void Minifying(ifstream &input_file, ofstream &output_file);
 int main() {
    ifstream file("input_file.xml");
    ofstream file2("output_file.xml");
    Minifying(file, file2);
    file.close();
    file2.close();
    cout << "File minified successfully";
    return 0;
 }
 void remove_indentation(string& line)
 {
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
 }
 void Minifying(ifstream &input_file, ofstream &output_file)
 {
    bool in_comment=false,in_tag=false,between_tags=false,notext=false;
    int notext_counter=0,text_detected,prsrv;
    string line;
    while (getline(input_file, line))
    {

        //loop on every character in the line
        for(int i=0;i<line.length();i++)
        {
            text_detected=0;
            //switch on that character
            switch(line[i])
            {
                case'<':
                        in_tag=true; //if you detect < so you are inside a tag
                    //if you detect <!-- so you are inside a comment
                    if(i+3<line.length()&&line[i+1]=='!'&&line[i+2]=='-'&&line[i+3]=='-')
                    {
                        in_comment=true;
                        in_tag=true;
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
                        between_tags=true;
                        in_tag=false;
                        //skip -->
                        i+=3;
                        continue;
                    }
                    break;
            }
            //skip comments
            if(in_comment)
                continue;
             if(between_tags)
            {
                prsrv=i;
                while(i < line.length() &&line[i]!='<')
                    {
                        if(line[i]==' '||line[i]=='\n'|| line[i]=='\r'||line[i]=='\t')
                            i++;
                        else
                        {
                            text_detected=1;
                            break;
                        }

                    }
                    i=prsrv;
            }
            if(text_detected==0)
            {
                //remove indentation from extracted line
                remove_indentation(line);
                output_file<<line[i];
            }
            else
                output_file<<line[i];

        }
    }
 }
