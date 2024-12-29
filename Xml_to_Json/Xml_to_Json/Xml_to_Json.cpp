#include <iostream>
//#include <fstream>
//#include <string>
//#include <stack>
//#include <vector>
//#include <algorithm>

#include "Xml_to_Json.h"
#include "../../Validity_checker/isValid.h"

using namespace std;

void Xml_to_Json(const string& input, const string& output) {
    ifstream inputFile(input);
    ofstream outputFile(output);
    /*if (inputFile.tellg() == 0)                      //if there is no code in the file
    {
        cout << "The input file path " << input << " is empty. Please provide a valid file.\n";
        outputFile<<"";
        return;
    }*/
    if (!isValid(input))                   //if xml file not valid
    {
        cout << "The input file: " << input << " is invalid please choose another one" << endl;
        outputFile<<"";
        return;
    }
    if (!inputFile.is_open())               // if there is no file with this name in this path
    {
        cout << "Unable to open input file: " << input << endl;
        outputFile<<"";
        return;
    }
    if (!outputFile.is_open())              // if there is no file with this name in this path
    {
        cout << "Unable to open output file: " << output << endl;
        return;
    }

    string line, tag_name = "", json_code = "{\n";
    // for carrying lines from xml file, tag name & code after formatting
    int tabs = 1, no_of_tags = 0;           // tabs to adjust identations, number of tags to see set or not
    stack<string> tags;                     // Handle all opening tags in the code & pop when is closed
    stack<vector<string>> parents_tag;      // Handle a vector of tags for one line   
    parents_tag.push({});                   // Intialize with empty vector
    stack<string> array;                    // Handle tag of the array to check to if array or not
    stack<string> before_array;             // Handle tags before the array to check to close the array
    stack<string> prev_before_array;        // Handle tag before the array tag by two to see when the array starts
    bool close = true;                      // Check if tag needs '},' to close or not 
    stack<string> temp;                     // temporary stack to fill prev_before_set stack
    stack<bool> set;                        // to increase the indentations by one if exist in an array
    set.push(false);                        // initialize start as not a set

    while (getline(inputFile, line)) {

        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        // Handle comments (ignore them completely)
        int commentStart = line.find("<!--");
        int commentEnd = line.find("-->");
        if (commentStart != -1) {
            // If the comment is in a single line, skip it
            if (commentEnd != -1 && commentEnd > commentStart) {
                continue;
            }
            else {
                // Skip multi-line comments
                while (commentEnd == -1 && getline(inputFile, line)) {
                    commentEnd = line.find("-->");
                }
                continue;
            }
        }
        // Handle tags
        int start_of_tag = line.find('<');
        int end_of_tag = line.find('>');
        string remainder = line.substr(end_of_tag + 1);
        bool same_line = !remainder.empty() ? true : false; //See if opening and closing is in the same line

        if (start_of_tag < line.size() && start_of_tag >= 0 && end_of_tag < line.size() && end_of_tag >= 0) {
            string tagContent = line.substr(start_of_tag + 1, end_of_tag - start_of_tag - 1);
            // Handle closed tags
            if (tagContent[0] == '/')
            {
                string closing_tag = tagContent.substr(1);
                tabs--;                //decrease identations by one
                if (!tags.empty() && tags.top() == closing_tag) {
                    tags.pop();
                    vector<string>& parents = parents_tag.top();    //call the top vector in the parents_tag stack
                    parents_tag.pop();

                    //count number of this tag in the line
                    no_of_tags = count(parents.begin(), parents.end(), closing_tag);

                    if (!prev_before_array.empty() && closing_tag == prev_before_array.top())
                    {
                        //if closing = the tag before the array tag by two && number of [ more than ] && we didn't close this array before add a closing tab
                        //i.e. array consisting more than two elements
                        if (count(json_code.begin(), json_code.end(), '[') > count(json_code.begin(), json_code.end(), ']'))
                        {
                            while (json_code.back() != ',')json_code.pop_back();
                            json_code.pop_back();
                            if (json_code.back() == ']') // if closed don't add ] just , 
                            {
                                json_code += ", \n";
                            }
                            else {
                                json_code += "\n" + string(tabs + 1, '\t') + "],\n"; //close array add ],
                                if (set.top())set.pop(); // if we close the array pop from the set array

                            }
                        }
                        prev_before_array.pop();
                    }
                    if (!close) //if the opening tag and closing tag are in the same line don't close with }
                    {
                        close = true; //reset indicator 
                        json_code += "\n";
                    }
                    else        // else close with }
                    {
                        while (json_code.back() != ',')json_code.pop_back();
                        json_code.pop_back();
                        json_code += "\n" + string(set.top() ? tabs + 1 : tabs, '\t') + "},\n";
                    }
                    if (!before_array.empty() && closing_tag == before_array.top()) // if array close with ],
                    {
                        array.push(before_array.top());
                        before_array.pop();
                        while (json_code.back() != ',')json_code.pop_back();
                        json_code.pop_back();
                        if (set.top())set.pop();
                        json_code += "\n" + string((set.top()) ? tabs + 1 : tabs, '\t') + "],\n";
                    }
                    else if (!array.empty() && closing_tag == array.top()) // if array close with ],
                    {
                        if (set.top())set.pop();
                        json_code += string(set.top() ? tabs + 1 : tabs, '\t') + "],\n";
                    }
                    else if (!array.empty() && closing_tag != array.top()) // if tag after array pop array.top
                    {
                        if (!array.empty())array.pop();
                    }
                }

            }
            else {
                int spacePos = tagContent.find(' ');
                bool selfClosing = tagContent.back() == '/';
                tag_name = (spacePos != -1) ? tagContent.substr(0, spacePos) : tagContent;
                if (tag_name.back() == '/') {
                    tag_name.pop_back();
                }
                vector<string>& parent = parents_tag.top();
                parent.push_back(tag_name);

                if (selfClosing)  //Handle self closing tags
                {
                    json_code += string(set.top() ? tabs + 1 : tabs, '\t') + "\"" + tag_name + "\": \"\",\n";
                }
                else
                {
                    if (!same_line)
                    {
                        no_of_tags = count(parent.begin(), parent.end(), tag_name);
                        if (no_of_tags == 2) // if array 
                        {
                            // save element which is before array [] by two to prev_before_array stack
                            while (true)
                            {
                                int t = 0;
                                while (!tags.empty() && t == 2)
                                {
                                    if (!tags.empty())
                                    {
                                        if (tag_name == tags.top())t++;
                                        temp.push(tags.top());
                                        tags.pop();
                                    }
                                }
                                if (!tags.empty())prev_before_array.push(tags.top());
                                while (!temp.empty())
                                {
                                    tags.push(temp.top());
                                    temp.pop();
                                }
                                break;
                            }
                            // after the array tag add [
                            string s = "\"" + tag_name + "\": ";
                            int x = json_code.rfind(s);
                            string y = json_code.substr(x + tag_name.size() + 4);
                            json_code = json_code.substr(0, x + tag_name.size() + 4) + "[\n"
                                + string(tabs, '\t');
                            int start = 0;
                            int end;
                            while ((end = y.find('\n', start)) != -1) {  //add tabs at beginning of each line in the array block to adjust indentations
                                json_code += "\t" + y.substr(start, end - start) + "\n";
                                start = end + 1;
                            }
                            before_array.push(tag_name);
                            set.push(true); //push a true to indicate exsistance of array 
                        }
                        else if (!array.empty() && tag_name == array.top())
                        //if array is closed but still there is an element from it remove ]
                        // i.e. more than two elements in the array
                        {
                            while (json_code.back() != '}')json_code.pop_back(); 
                            set.push(true);
                            json_code += ", \n";
                        }
                        //if only one tag add "tag name" : {
                        if (no_of_tags == 1)
                        {
                            json_code += string(set.top() ? tabs + 1 : tabs, '\t') + "\"" + tag_name + "\": {\n";
                        }
                        else //if more than 1 or 2 don't put tag name again only {
                        {
                            json_code += string(set.top() ? tabs + 1 : tabs, '\t') + "{\n";
                        }

                        tags.push(tag_name);
                        parents_tag.push({});
                        tabs++;
                    }

                }
            }
            //if opening and closing are in same line then content is between them parse the the add to json code
            int contentStart = end_of_tag + 1;
            int contentEnd = line.find('<', contentStart);
            if (contentEnd != -1 && contentEnd > contentStart)
            {
                string content = line.substr(contentStart, contentEnd - contentStart);
                if (!content.empty())
                {
                    json_code += string(set.top() ? tabs + 1 : tabs, '\t') + "\"" + tag_name + "\": \"" + content + "\",\n";
                }
            }

        }
        else
        {
            string not_tags = "\"";
            bool started = 0;
            // Parse the data 'not tag' 
            for (int j = 0; j < line.size(); j++)
            {
                if (!started)
                {
                    //remove the tabs or spaces at beginning of the data
                    if (line[j] == ' ' || line[j] == '\t') 
                    {
                        continue;
                    }
                }
                started = 1;
                not_tags += line[j];
            }
            close = false;
            not_tags += "\", ";
            json_code.pop_back(); //remove '\n'
            json_code.pop_back(); //remove ','
            json_code += not_tags;
        }
    }
    while (json_code.back() != '}')json_code.pop_back(); // Remove all characters before '}' to finalize the code
    json_code += "\n}\n";
    cout << json_code;
    outputFile << json_code;                            // Print code in output file

    inputFile.close();
    outputFile.close();
}

/*int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: xml_editor json -i input_file.xml -o output_file.json\n";
        return 1;
    }

    string operation = argv[1];
    string inputFileName, outputFileName;

    for (int i = 2; i < argc; i += 2) {
        string flag = argv[i];
        if (flag == "-i") {
            inputFileName = argv[i + 1];
        }
        else if (flag == "-o") {
            outputFileName = argv[i + 1];
        }
    }

    if (operation == "json") {
        Xml_to_Json(inputFileName, outputFileName);
    }
    else {
        cerr << "Invalid operation. Use 'json' only." << endl;
        return 1;
    }
    return 0;
}*/

//int main() {
//    string inputFilePath = "../../Test_samples/Xml_to_Json/sample_invalid.xml";
//    string outputFilePath = "../../Test_samples/Xml_to_Json/output_file_json4.json";
//    Xml_to_Json(inputFilePath, outputFilePath);
//    return 0;
//}
