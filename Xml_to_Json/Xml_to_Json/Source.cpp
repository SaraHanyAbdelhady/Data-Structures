#include <iostream>
#include <fstream>
#include <string>

using namespace ::std;


void Xml_to_Json(const string& input, const string& output) {
    ifstream inputFile(input);
    ofstream outputFile(output);
    if (!inputFile.is_open()) 
    {
        cout << "Unable to open input file: " << input << std::endl;
        return;
    }
    if (!outputFile.is_open()) 
    {
        cout << "Unable to open output file: " << output << std::endl;
        return;
    }
    string line;
    string line_dash = "";
    string json_code = "{\n";
    int tabs = 1;
    string tag_name_old = "";
    string tag_name = ""; 
    while (getline(inputFile, line)) {
        int i;
        string block;
        while (1)
        {   
            block += line;
            for (i = 0;i < line.size() - 1;i++)
            {
                if (line[i] == '<' && line[i + 1] == '/')
                {
                    break;
                }
            }
            block += ' ';
            getline(inputFile, line);
        }
        bool set;
        for (i = 0;i < block.size();i++)
        {

            if (block[i] == '<' && line[i + 1] == '/')
            {
                if(set) line_dash += '},';
                else line_dash += ',';
            }
            else if (line[i] == '<')           //&& line[i+1] != '/'
            {
                tabs++;
                line_dash += '"';
                for (++i;line[i] == '>';i++)
                {
                    tag_name += line[i];
                    line_dash += line[i];
                }
                line_dash += "\": ";
                if (tag_name == tag_name_old.substr(0, tag_name_old.size() - 1))
                {
                    line_dash += '[';

                }
                else if (tag_name == tag_name_old)
                {
                    line_dash = "{";
                }
                else 
                {
                    line_dash += "{";
                    tag_name_old = tag_name ;
                    tag_name = "";
                }
                if (i == line.size())      //&& line_dash[line_dash.size() - 1] == '{' || '['
                {
                    json_code += string(tabs, '\t');
                    json_code += line_dash;
                    line_dash = "";
                    json_code += '\n';
                    tabs++;
                    continue; //equivalent to break
                }
            }

            

        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFilePath = "../../sample.xml";
    string outputFilePath = "../../output_file_json.json";
    Xml_to_Json(inputFilePath, outputFilePath);
    return 0;
}
