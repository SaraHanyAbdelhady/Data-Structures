# 🛠️ XML Parser and Social Network Visualizer

## 🌟 Overview
This project is a comprehensive desktop application for processing and visualizing XML data, designed to represent social network data effectively. The application supports both **⚙️ Command-Line** and **🖥️ GUI** modes, offering flexibility for various user preferences. It provides tools to analyze XML files, correct inconsistencies, convert formats, and visualize user relationships.

---

## ✨ Key Features

### 📌 Level 1 Requirements
1. **🔍 XML Consistency Checking**  
   - Detects inconsistencies in XML files (e.g., unmatched tags).  
   - Fixes errors and outputs corrected files.  

2. **🎨 XML Prettifying**  
   - Formats XML files with proper indentation for better readability.  

3. **🔄 XML to JSON Conversion**  
   - Converts XML files to JSON format for enhanced compatibility.  

4. **📉 Minifying XML**  
   - Removes unnecessary spaces and newlines to reduce file size.  

5. **📦 Compression and Decompression**  
   - Uses data compression techniques (e.g., Byte Pair Encoding) to reduce file size.  
   - Decompresses files to restore the original format.

---

### 📌 Level 2 Requirements
1. **🌐 Social Network Graph Representation**  
   - Represents user relationships (followers, posts, etc.) as a graph.  
   - Visualizes the graph using graphical tools or libraries.  

2. **📊 Network Analysis**  
   - Identifies:  
     - 🌟 Most influential user.  
     - 🔗 Most active user.  
     - 🤝 Mutual followers between users.  
   - Suggests new connections based on analysis.  

3. **🔎 Post Search**  
   - Searches for posts containing specific **keywords** or **topics**.  

4. **📈 Graph Visualization**  
   - Visualizes user connections interactively and intuitively.

---

## ⚙️ Usage

### 💻 Command-Line Mode
The application supports various commands:  
- **Verify XML**:  
  ```bash
  xml_editor verify -i input_file.xml [-f] [-o output_file.xml]
### 🔄 Convert XML to JSON:
  ```bash
xml_editor json -i input_file.xml -o output_file.json
```
### 📉 Minify XML:
  ```bash
xml_editor mini -i input_file.xml -o output_file.xml
```
### 📦 Compress XML:
  ```bash
xml_editor compress -i input_file.xml -o output_file.comp
```
### 🗜️ Decompress XML:
  ```bash

xml_editor decompress -i input_file.comp -o output_file.xml
```
## 📊 Network Analysis

### 🏆 Find Most Active User
```bash
xml_editor most_active -i input_file.xml
```
### 🌟 Find Most Influencer User
```bash
xml_editor most_influencer -i input_file.xml
```
### 🤝 Find Mutual Followers
```bash
xml_editor mutual -i input_file.xml -ids 1,2,3
```
### 🔗 Suggest Users to Follow
``` bash
xml_editor suggest -i input_file.xml -id 1
```
### 🖥️ GUI Mode
- **File Upload**: Use the browse button to upload XML files.
- **Operations**: Click buttons to perform operations like prettifying, minifying, or converting XML.
- **View Results**: View operation results in a read-only text area.
- **Save Outputs**: Save processed files to your desired location.
