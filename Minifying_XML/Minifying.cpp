#include "Minifying.h"
int main()
{
    ifstream file1("input_file.xml");
    ofstream file2("output_file.xml");
    Minifying(file1, file2);
    file1.close();
    file2.close();
    return 0;
}
void Minifying(ifstream& input_file, ofstream& output_file) {
    stringstream buffer;
    buffer << input_file.rdbuf();
    string fileContent = buffer.str();
    //Now we have all the content of input_file in the string fileContent
    bool in_tag = false, in_comment = false; //flags to indicate inside tags and inside comment
    queue<char> result; //queue to store the result to output it in file at the end
    string content_between_tags; //string to preserve the content between tags > and <
    //loop on every character in the file
    for (int i = 0; i < fileContent.length(); i++)
    {
        //if inside comment so skip it
        if (in_comment)
        {
            if (i + 2 < fileContent.length() && fileContent[i] == '-' && fileContent[i + 1] == '-' && fileContent[i + 2] == '>')
            {
                in_comment = false;
                i += 2; // to skip -->
            }
            continue;
        }
        //if you detect < so you are inside tag
        if (fileContent[i] == '<')
            {
            if (i + 3 < fileContent.length() && fileContent[i + 1] == '!' && fileContent[i + 2] == '-' && fileContent[i + 3] == '-')
            {
                in_comment = true;
                i += 3; // Skip <!--
                continue;
            }

            // If there was content between tags and it only contains space or \n or \t or \r, remove it
            if (!content_between_tags.empty()) // this condition check if there is anything between tags
                {

                        // If not only whitespace so add it as it is to result,don't change anything in it
                        //isspace is a function that checks if the string has whitespaces only or not

                    if (!(all_of(content_between_tags.begin(), content_between_tags.end(), ::isspace)) )
                    {
                    for (char ch : content_between_tags)
                        result.push(ch);

                    }
                    content_between_tags=""; //empty the string when you finish
                }
            //since you detected < so you are between tags
            in_tag = true;
            //add the character to result
            result.push(fileContent[i]);
        }
        //if you detect > so set in_tag to false and add to result the >
        else if (fileContent[i] == '>')
        {
            in_tag = false;
            result.push(fileContent[i]);
        }
        //if you are inside tag so do not change anything, we leave what is between tags as it is
        else if (in_tag)
            result.push(fileContent[i]);
        // if you do not detect < or > and you are not inside tags then you are between tags
        else
        {
            //before adding what is between tags to result, we need to check if all content between tags is whitespace
            // if that happens so we do not add anything between tags to result, if not so simply add the content just as it is with no change
            // Check if content until the next < is all whitespace
            int next_tag = fileContent.find('<', i);
            if (next_tag != -1) //not equal -1 means found < because if it didnt find so it returns -1
            {
                string between_tags = fileContent.substr(i, next_tag - i); //put content between the tags in string between_tags
                if(!(all_of(between_tags.begin(), between_tags.end(), ::isspace)) )
                {
                   for (char tt : between_tags)
                        result.push(tt);
                }
                i = next_tag - 1; //skip the content we added to result
            }
        }
    }
    //write result to output file
    while (!result.empty())
    {
        output_file<<result.front();
        result.pop();
    }
}

