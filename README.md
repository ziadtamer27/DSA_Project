---

# **XML Editor & Social Network Analyzer**

This project is a C++ desktop tool (CLI + GUI later) that processes XML files representing a social network.
It supports XML validation, formatting, minifying, conversion to JSON, custom compression, decompression, and graph-based network analysis.

---

## 📁 **Project Structure**

```
.
├── README.md
├── xml_editor.exe
│
├── inputXMLfiles
│   └── sample.xml
│
├── outputfiles
│   ├── compresed_file.xml
│   ├── decompressed_file.xml
│   └── JSON_output.json
│
└── src
    ├── code
    │   ├── CheckXmlFile.cpp
    │   ├── CompressingXMLFile.cpp
    │   ├── DecompressingXMLFile.cpp
    │   ├── main.cpp
    │   ├── MinifyingXMLFile.cpp
    │   ├── NetworkBuilder.cpp
    │   ├── XMLtoJSON.cpp
    │   └── XMLtoTree.cpp
    │
    └── header
        ├── CheckXmlFile.h
        ├── CompressingXML.h
        ├── DecompressingXML.h
        ├── MinifyingXMLFile.h
        ├── NetworkBuilder.h
        ├── XMLtoJSON.h
        └── XMLtoTree.h
```

---

## ⚙️ **Build Instructions**

Compile all `.cpp` files at once:

```bash
g++ src/code/*.cpp -o xml_editor.exe
```

Run:

```bash
./xml_editor.exe
```

---

## 🚀 **Supported CLI Operations**

| Operation                | Command Example                                     | Description                              |
| ------------------------ | --------------------------------------------------- | ---------------------------------------- |
| **Verify XML**           | `xml_editor verify -i sample.xml`                   | Checks XML consistency & reports errors. |
| **Fix XML**              | `xml_editor verify -i sample.xml -f -o fixed.xml`   | Repairs mismatched/missing tags.         |
| **Format XML**           | `xml_editor format -i sample.xml -o formatted.xml`  | Beautifies XML with indentation.         |
| **Minify XML**           | `xml_editor mini -i sample.xml -o mini.xml`         | Removes whitespace to reduce size.       |
| **Convert to JSON**      | `xml_editor json -i sample.xml -o output.json`      | Converts XML → JSON.                     |
| **Compress XML**         | `xml_editor compress -i sample.xml -o out.comp`     | Custom compression (BPE-like).           |
| **Decompress XML**       | `xml_editor decompress -i out.comp -o restored.xml` | Restores full XML.                       |
| **Build Network Graph**  | `xml_editor draw -i sample.xml -o graph.jpg`        | Builds graph from users/followers.       |
| **Most Active User**     | `xml_editor most_active -i sample.xml`              | User with most outgoing connections.     |
| **Most Influencer User** | `xml_editor most_influencer -i sample.xml`          | User with most followers.                |
| **Mutual Followers**     | `xml_editor mutual -i sample.xml -ids 1,2,3`        | Common followers.                        |
| **Suggestions**          | `xml_editor suggest -i sample.xml -id 1`            | Recommended users to follow.             |
| **Search Posts**         | `xml_editor search -w word -i sample.xml`           | Search posts by word/topic.              |

---

## 📦 **Modules Overview**

### **1️⃣ XML Parsing**

* Converts raw XML into a tree structure.
* Detects mismatched, missing, or malformed tags.
* Implemented in:
  `XMLtoTree.cpp`, `CheckXmlFile.cpp`

### **2️⃣ XML Formatting & Minifying**

* Beautifies XML with indentation.
* Produces compact versions (minified).
* Implemented in:
  `MinifyingXMLFile.cpp`

### **3️⃣ JSON Conversion**

* Recursively converts XML tree → JSON format.
* Supports arrays, nested objects, and text nodes.
* Implemented in:
  `XMLtoJSON.cpp`

### **4️⃣ Compression & Decompression**

* Custom text compression algorithm (BPE-inspired).
* Saves compressed output as `.comp`.
* Implemented in:
  `CompressingXMLFile.cpp`, `DecompressingXMLFile.cpp`

### **5️⃣ Network Graph Construction**

* Builds graph from `<user>` and follower relationships.
* Supports analysis operations:

  * most active
  * most influencer
  * mutual followers
  * suggestions
* Implemented in:
  `NetworkBuilder.cpp`

---

## 🧪 **Test XML Files**

Located in `XMLfiles/`:

* `sample.xml`
* `compressed_file.xml`
* `decompressed_file.xml`

---

## 📌 **Planned Additions**

* GUI Mode (Qt / wxWidgets / SFML / ImGui)
* Graph visualization (PNG/JPG export)
* Search indexing optimization
* Further compression improvements

---

