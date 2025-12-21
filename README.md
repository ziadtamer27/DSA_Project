---

## **XML Editor & Social Network Analyzer**

A C++ desktop tool for processing XML files that represent a social network.
The project supports **CLI mode** and a **ready-to-run GUI mode** (no Qt installation required).

---

## 📁 **Project Structure**

```
.
├── README.md
│
├── CLI_mode
│   ├── xml_editor.exe
│   ├── inputXMLfiles
│   │   └── sample.xml
│   ├── outputfiles
│   │   ├── compresed_file.comp
│   │   ├── decompressed_file.xml
│   │   └── JSON_output.json
│   └── src
│       ├── code
│       └── header
│
└── GUI
    ├── Release
    │   └── xml_editor_gui.exe
    └── src_code
```

---

## 🚀 **How to Run**

### 🔹 GUI Mode (Recommended)

✔ **No build required**
✔ **No Qt installation needed**

Just run:

```
GUI/Release/xml_editor_gui.exe
```

---

### 🔹 CLI Mode

Run the executable from `CLI_mode`:

```bash
xml_editor.exe <command> [options]
```

---

## 🧰 **Supported CLI Operations**

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

## 📦 **Core Features**

### **XML Processing**

- XML validation and auto-fixing
- Formatting (pretty print)
- Minifying

### **Conversion**

- XML → JSON conversion with full hierarchy support

### **Compression**

- Custom BPE-inspired compression
- Full decompression back to original XML

### **Social Network Analysis**

- Graph-based user & follower representation
- Influence and activity metrics
- Mutual followers & suggestions
- Post search by keywords

---

## 🖥️ **GUI Mode Features**

- Windows desktop application
- No external dependencies required
- File picker for input/output
- Command selector (verify, minify, json, compress, etc.)
- Preview windows for:

  - XML
  - JSON
  - Logs / messages

- Internally wraps the same logic as the CLI

---

## 📌 **Notes**

- GUI executable is **prebuilt and ready**
- Source code for both CLI and GUI is included
- CLI and GUI share the same processing backend

---
