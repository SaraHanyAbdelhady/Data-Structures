#include <iostream>
//#include <fstream>
//#include <string>
//#include <stack>
//#include <vector>
//#include <algorithm>

#include "Xml_to_Json.h"
#include "../../Validity_checker/isValid.h"
//#include "../../Minifying/minify.h"

using namespace std;

void Xml_to_Json(const string& input, const string& output) {
    /*
        inputFilePath = input;
        string outputFilePath = "../../minified.xml"
        minify(inputFilePath,outputFilePath);
        input = outputFilePath;
    */
    ifstream inputFile(input);
    ofstream outputFile(output);
    if (input.empty())
    {
        cout << "The input file path " << input << "is empty. Please provide a valid file.\n";
        return;
    }
    /*if(!valid(input))
    {
        cout << "The input file: " << input << "is invalid please choose another one" << endl;
        return;
    }*/
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << input << endl;
        return;
    }
    if (!outputFile.is_open())
    {
        cout << "Unable to open output file: " << output << endl;
        return;
    }

    string line, tag_name = "", json_code = "{\n";
    int tabs = 0, no_of_tags = 0;
    stack<string> tags;
    stack<vector<string>> parents_tag;
    stack<string> before_set;
    parents_tag.push({});
    stack<string> prev_before_set;
    bool close = true;
    stack<string> temp;
    stack<string> before_array;
    stack<bool> set;
    set.push(false);

    while (getline(inputFile, line)) {
        int start_of_tag = line.find('<');
        int end_of_tag = line.find('>');
        string remainder = line.substr(end_of_tag + 1);
        bool same_line = !remainder.empty() ? true : false;

        if (start_of_tag < line.size() && start_of_tag >= 0 && end_of_tag < line.size() && end_of_tag >= 0) {
            string tagContent = line.substr(start_of_tag + 1, end_of_tag - start_of_tag - 1);

            if (tagContent[0] == '/')
            {
                string closing_tag = tagContent.substr(1);
                tabs--;
                if (!tags.empty() && tags.top() == closing_tag) {
                    tags.pop();
                    vector<string>& parents = parents_tag.top();
                    parents_tag.pop();

                    no_of_tags = count(parents.begin(), parents.end(), closing_tag);
                    if (!before_array.empty() && closing_tag == before_array.top())
                    {
                        if (count(json_code.begin(), json_code.end(), '[') > count(json_code.begin(), json_code.end(), ']'))
                        {
                            while (json_code.back() != ',')json_code.pop_back();
                            json_code.pop_back();
                            if (json_code.back() == ']')
                            {
                                json_code += ", \n";
                            }
                            else {
                                if (set.top())set.pop();
                                json_code += "\n" + string(tabs + 2, '\t') + "],\n";
                                
                            }
                        }
                        before_array.pop();
                    }
                    if (!close)
                    {
                        close = true;
                        json_code += "\n";
                    }
                    else
                    {
                        while (json_code.back() != ',')json_code.pop_back();
                        json_code.pop_back();
                        json_code += "\n" + string(set.top() ? tabs + 2 : tabs + 1, '\t') + "},\n";
                    }
                    if (!before_set.empty() && closing_tag == before_set.top())
                    {
                        prev_before_set.push(before_set.top());
                        before_set.pop();
                        while (json_code.back() != ',')json_code.pop_back();
                        json_code.pop_back();
                        if (set.top())set.pop();
                        json_code += "\n" + string((set.top() )? tabs + 2 : tabs + 1, '\t') + "],\n";
                    }
                    else if (!prev_before_set.empty() && closing_tag == prev_before_set.top())
                    {
                        if (set.top())set.pop();
                        json_code += string(set.top() ? tabs + 2 : tabs + 1, '\t') + "],\n";
                    }
                    else if (!prev_before_set.empty() && closing_tag != prev_before_set.top())
                    {
                        if (!prev_before_set.empty())prev_before_set.pop();
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

                if (selfClosing)
                {
                    json_code += string(set.top() ? tabs + 2 : tabs + 1, '\t') + "\"" + tag_name + "\": "",\n";
                }
                else
                {
                    if (!same_line)
                    {
                        no_of_tags = count(parent.begin(), parent.end(), tag_name);
                        if (no_of_tags == 2)
                        {
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
                                if (!tags.empty())before_array.push(tags.top());
                                while (!temp.empty())
                                {
                                    tags.push(temp.top());
                                    temp.pop();
                                }
                                break;
                            }
                            string s = "\"" + tag_name + "\": ";
                            int x = json_code.rfind(s);
                            string y = json_code.substr(x + tag_name.size() + 4);
                            json_code = json_code.substr(0, x + tag_name.size() + 4) + "[\n"
                                + string(tabs + 1, '\t') ;
                            int start = 0;
                            int end;
                            while ((end = y.find('\n', start)) != -1) {
                                json_code += "\t" + y.substr(start, end - start) + "\n";
                                start = end + 1;
                            }
                            before_set.push(tag_name);
                            set.push(true);
                        }
                        else if (!prev_before_set.empty() && tag_name == prev_before_set.top())
                        {
                            while (json_code.back() != '}')json_code.pop_back();
                            set.push(true);
                            json_code += ", \n";
                        }

                        if (no_of_tags == 1)
                        {
                            json_code += string(set.top() ? tabs + 2 : tabs + 1, '\t') + "\"" + tag_name + "\": {\n";
                        }
                        else
                        {
                            json_code += string(set.top() ? tabs + 2 : tabs + 1, '\t') + "{\n";
                        }

                        tags.push(tag_name);
                        parents_tag.push({});
                        tabs++;
                    }

                }
            }
            int contentStart = end_of_tag + 1;
            int contentEnd = line.find('<', contentStart);
            if (contentEnd != -1 && contentEnd > contentStart)
            {
                string content = line.substr(contentStart, contentEnd - contentStart);
                if (!content.empty())
                {
                    json_code += string(set.top()?tabs + 2:tabs + 1, '\t') + "\"" + tag_name + "\": \"" + content + "\",\n";
                }
            }

        }
        else
        {
            string not_tags = "\"";
            bool started = 0;
            for (int j = 0; j < line.size(); j++)
            {
                if (!started)
                {
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
            json_code.pop_back();
            json_code.pop_back();
            //if(set.top())json_code += "\t" ;
            json_code += not_tags;
        }
    }

    while (json_code.back() != ',')json_code.pop_back();
    json_code.pop_back();
    while (json_code.back() != '}')json_code.pop_back();
    json_code += "\n}\n";
    cout << json_code;
    outputFile << json_code;

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFilePath = "../../Test_samples/Xml_to_Json/sample3.xml";
    string outputFilePath = "../../Test_samples/Xml_to_Json/output_file_json3.json";
    Xml_to_Json(inputFilePath, outputFilePath);
    return 0;
}
