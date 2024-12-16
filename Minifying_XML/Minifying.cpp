#include "Minifying.h"
int main()
{
    ifstream input_file("input_file.xml");
    ofstream output_file("output_file.xml");
    Minifying(input_file, output_file);
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
    for (size_t i = 0; i < fileContent.size(); ++i) {
        char c = fileContent[i];
        //if inside comment so skip it
        if (in_comment) {
            if (i + 2 < fileContent.size() && fileContent[i] == '-' && fileContent[i + 1] == '-' && fileContent[i + 2] == '>') {
                in_comment = false;
                i += 2; // to skip -->
            }
            continue;
        }
        //if you detect < so you are inside tag
        if (c == '<') {
                //if < followed by !-- so its a comment
            if (i + 3 < fileContent.size() && fileContent[i + 1] == '!' && fileContent[i + 2] == '-' && fileContent[i + 3] == '-')
            {
                in_comment = true;
                i += 3; // Skip <!--
                continue;
            }

            // If there was content between tags and it only contains space or \n or \t or \r, remove it
            if (!content_between_tags.empty()) // this condition check if there is anything between tags
                {
                    if (all_of(content_between_tags.begin(), content_between_tags.end(), ::isspace)) {
                        // If only whitespace, don't add it to the result so do nothing
                        //isspace is a function that checks if the string has whitespaces only or not
                    }
                    else
                    { // that means there is non white space characters between tags so add all the content between tags to result as it is with no change
                    for (char ch : content_between_tags)
                        result.push(ch);

                    }
                    content_between_tags=""; //empty the string when you finish
                }
            //since you detected < so you are between tags
            in_tag = true;
            //add the character to result
            result.push(c);
        }
        //if you detect > so set in_tag to false and add to result the >
        else if (c == '>')
        {
            in_tag = false;
            result.push(c);
        }
        //if you are inside tag so do not change anything, we leave what is between tags as it is
        else if (in_tag)
            result.push(c);
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
                if (all_of(between_tags.begin(), between_tags.end(), ::isspace)) {
                    // If all content between tags is whitespace, only print the next < and do not print anything before it
                    if (result.empty() || result.back() != '<') ;
                }
                else
                {
                    // Otherwise, print all content
                   for (char ch : between_tags)
                        result.push(ch);
                }
                i = next_tag - 1; //skip the content we added to result
            }
        }
    }
    //write result to output file
    while (!result.empty())
    {
        output_file.put(result.front());
        result.pop();
    }
}

