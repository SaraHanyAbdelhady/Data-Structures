#include "Xml_to_Graph.h"
#include "../../parseXML/parseXML.h"

using namespace std;



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
        /*
        cout << graph[i].ID << endl << endl;
        cout << graph[i].name << endl << endl;
        for (int x = 0; x < graph[i].followers.size(); x++)cout << graph[i].followers[x] << endl << endl;
        for (int z = 0; z < graph[i].posts.size(); z++) {
            cout << graph[i].posts[z].body << endl << endl;
            for (int y = 0; y < graph[i].posts[z].topics.size(); y++)
            cout << graph[i].posts[z].topics[y] << endl << endl;
        }*/
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
    remove(outputJpg.c_str());
    // Step 1: Parse XML file
    parseXML(inputXML, graph);

    // Step 2: Generate DOT file
    string dotFile = "output.dot";
    generateDOT(graph, dotFile);

    // Step 3: Generate JPG image using Graphviz
    generateJPG(dotFile, outputJpg);
}

// Main function to handle command-line arguments
/*int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: xml_editor <operation> -i <input_file> -o <output_file>\n";
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

    if (operation == "draw") {
        Xml_to_Graph(inputFileName, outputFileName);
    }
    else {
        cerr << "Invalid operation. Use 'draw' only." << endl;
        return 1;
    }
    return 0;
}*/
//int main() {
//    string inputXML = "../../Test_samples/Xml_to_Graph/sample1.xml";
//    string outputJPG = "../../Test_samples/Xml_to_Graph/graph1.jpg";
//
//    Xml_to_Graph(inputXML, outputJPG);
//
//    return 0;
//}

