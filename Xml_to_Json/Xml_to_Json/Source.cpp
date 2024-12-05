#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

void Xml_to_Json(const string& input, const string& output) {
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
    int tabs = 1, no_of_tags = 0;
    stack<string> tags;
    stack<vector<string>> parents_tag;
    parents_tag.push({});
    vector<string> repeated_tags;
    bool close = true;

   
    while (getline(inputFile, line)) {
        int start_of_tag = line.find('<');
        int end_of_tag = line.find('>');
        string remainder = line.substr(end_of_tag + 1);

        bool same_line = !remainder.empty()? true: false;
        
        /*if (remainder.empty() && !close)
        {
            tabs--;
            json_code += ",\n";
            close = 1;
            continue;
        }*/
        if (start_of_tag < line.size() && start_of_tag >= 0 && end_of_tag < line.size() && end_of_tag >= 0) {
            string tagContent = line.substr(start_of_tag + 1, end_of_tag - start_of_tag - 1);
            if (tagContent[0] == '/') {
                string closing_tag = tagContent.substr(1);

                if (!tags.empty() && tags.top() == closing_tag) {
                    tags.pop();
                    vector<string>& parents = parents_tag.top();
                    parents_tag.pop();
                    tabs--;

                    no_of_tags = count(parents.begin(), parents.end(), closing_tag);
                    

                    if (no_of_tags > 1)
                    {
                        json_code.pop_back();
                        json_code += "\n" + string(tabs, '\t') + "]\n";
                    }
                    else
                    {
                        if (!close)
                        {
                            close = true;
                            json_code += "\n";
                        }
                        else
                        {
                            while(json_code.back() != ',')json_code.pop_back();
                            json_code.pop_back();
                            json_code += "\n" + string(tabs, '\t') + "},\n";
                        }
                        
                    }
                }
            }
            else {
                int spacePos = tagContent.find(' ');
                bool selfClosing = tagContent.back() == '/';
                tag_name = (spacePos != -1) ? tagContent.substr(0, spacePos) : tagContent;

                vector<string>& parent = parents_tag.top();
                parent.push_back(tag_name);
                repeated_tags.push_back(tag_name);
                if (selfClosing)
                {
                    json_code += string(tabs, '\t') + "\"" + tag_name + "\": null,\n";
                }
                else 
                {
                    if (!same_line )
                    {
                        no_of_tags = count(parent.begin(), parent.end(), tag_name);
                        
                        if (no_of_tags == 1 || tag_name.back() == 's')
                        {
                            json_code += string(tabs, '\t') + "\"" + tag_name + "\": {\n";
                        }
                        else if (parent[parent.size() - 2] == tag_name + "s")
                        {
                            json_code.pop_back();
                            json_code += string(tabs, '\t') + "\"" + tag_name + "\": [\n";
                        }
                        else
                        {
                            json_code += string(tabs + 1, '\t') + "{\n";
                        }

                        tags.push(tag_name);
                        parents_tag.push({});
                        tabs++;
                    }
                    
                }
            }
            int contentStart = end_of_tag + 1;
            int contentEnd = line.find('<', contentStart);
            if (contentEnd != - 1 && contentEnd > contentStart)
            {
                string content = line.substr(contentStart, contentEnd - contentStart);
                if (!content.empty())
                {
                    json_code += string(tabs, '\t') + "\"" + tag_name + "\": \"" + content + "\",\n";
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
            json_code += not_tags;
        }
    }

    while (json_code.back() != ',')json_code.pop_back();
    json_code.pop_back();
    json_code += "\n}\n";

    cout << json_code;
    outputFile << json_code;

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFilePath = "../../sample.xml";
    string outputFilePath = "../../output_file_json.json";
    Xml_to_Json(inputFilePath, outputFilePath);
    return 0;
}

