#include "Xml_to_Graph.h"

using namespace std;

// class to carry id & followers in one item
class user {
public:
    int ID;
    vector<int> followers;
    user() {
        ID = 0;
        followers = {};
    }
    user(int x) {
        ID = x;
        followers = {};
    }
    user(int x, vector<int>y) {
        ID = x;
        followers = y;
    }
};

// Function to parse XML and build a graph
void parseXML(const string& filename, vector<user>& graph)
{

    ifstream inputFile(filename);
    // if error in opening xml file
    if (!inputFile.is_open())
    {
        cout << "Unable to open input file: " << filename << std::endl;
        return;
    }
    string line;                //to read line by line from the xml file
    stack<string> tags;         //to store tags
    user User;                  // dammy user to fill graph vector
    bool in_follower = false;   //to see if id is from user or followers
    while (getline(inputFile, line)) {

        if (line.empty()) continue;

        int start_of_tag = line.find('<');
        int end_of_tag = line.find('>');
        string remainder = line.substr(end_of_tag + 1);

        if (start_of_tag < line.size() && start_of_tag >= 0 && end_of_tag < line.size() && end_of_tag >= 0) {
            string tagContent = line.substr(start_of_tag + 1, end_of_tag - start_of_tag - 1);
            // check opening tags
            if (tagContent[0] != '/') {
                tags.push(tagContent);
                if (tagContent == "user") {
                    User = user(); // initialize user
                }
                else if (tagContent == "follower") {
                    in_follower = true;
                }
                else if (tagContent == "id") {
                    // in case the opening and closing are in the same line
                    if (!remainder.empty()) {
                        string id_string = remainder.substr(0, remainder.find('<'));
                        if (in_follower) {
                            User.followers.push_back(stoi(id_string));
                        }
                        else {
                            User.ID = stoi(id_string);
                        }
                        if (!tags.empty()) tags.pop();
                    }
                }
            }
            //check closing tags
            else if (tagContent[0] == '/') {
                string closingTag = tagContent.substr(1, tagContent.length() - 1);
                if (closingTag == "user") {
                    // Add user to vector
                    graph.push_back(User);
                }
                else if (closingTag == "follower") {
                    in_follower = false;
                }

                if (!tags.empty()) tags.pop();
            }
        }
        //in case the tag is opened and not closed in the sme line
        else {
            if (!tags.empty()) {
                string currentTag = tags.top();

                if (currentTag == "id") {
                    if (in_follower) {
                        User.followers.push_back(stoi(line));
                    }
                    else {
                        User.ID = stoi(line);
                    }
                }
            }
        }
    }
    inputFile.close();
}

// Function to generate a DOT file for Graphviz
void generateDOT(const vector<user>& graph, const string& outputFile) {

    ofstream file(outputFile);
    // if error in opening output file
    if (!file.is_open()) {
        cout << "Error opening file for DOT output!" << endl;
        exit(1);
    }
    //display data in dot form 
    file << "digraph G {\n";
    file << "    graph[fontsize = 24]\n";
    file << "    edge[fontsize = 20 color = burlywood]\n";
    file << "    node[margin=0 fontcolor=cornsilk fontsize=48 width=0.5 shape=circle style=filled fillcolor = darkorchid4]\n";
    file << "    ranksep = 1.5\n";
    file << "    nodesep = .25\n";
    file << "    edge[style = \"setlinewidth(3)\"]\n";
    for (int i = 0; i < graph.size();i++) {
        for (int j = 0; j < graph[i].followers.size(); j++) {
            file << "    " << graph[i].ID << " -> " << graph[i].followers[j] << ";\n";
        }
    }
    file << "}\n";

    file.close();
    cout << "DOT file generated: " << outputFile << endl;
}

// Function to generate a JPG image using Graphviz
void generateJPG(const string& dotFile, const string& jpgFile) {
    // generating cmd command line to call Graphviz
    string command = "dot -Tjpg " + dotFile + " -o " + jpgFile;

    int result = system(command.c_str());   // call Graphviz using cmd
    if (result == 0) {
        cout << "Graph image generated: " << jpgFile << endl;
    }
    else {
        //if cmd returns a string it means an error occured when calling Graphviz
        cout << "Error generating JPG file. Ensure Graphviz is installed!" << endl;
    }
}

void Xml_to_Graph(const string& inputXML, const string& outputJpg) {

    vector<user> graph; //as we pass it with reference 

    // Step 1: Parse XML file
    parseXML(inputXML, graph);

    // Step 2: Generate DOT file
    string dotFile = "../../Test_samples/Xml_to_Graph/output2.dot";
    generateDOT(graph, dotFile);

    // Step 3: Generate JPG image using Graphviz
    generateJPG(dotFile, outputJpg);
}
int main() {
    string inputXML = "../../Test_samples/Xml_to_Graph/sample1.xml";
    string outputJPG = "../../Test_samples/Xml_to_Graph/graph1.jpg";

    Xml_to_Graph(inputXML, outputJPG);

    return 0;
}

