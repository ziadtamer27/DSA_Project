---

## **XML Editor & Social Network Analyzer**

A C++ desktop tool for processing XML files that represent a social network.
The project supports **CLI mode** and a **ready-to-run GUI mode** (no Qt installation required).

### GUI Screenshot

<img width="1453" height="1079" alt="Screenshot 2025-12-24 193829" src="https://github.com/user-attachments/assets/076adb60-edd6-4fcd-a113-169876f712e7" />


---

## 📁 **Project Structure**

```
.
├── README.md
│
├── CLI_mode
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
    └── src_code
```

---

## 🧰 **Supported CLI Operations**

| Operation                | Command Example                                         | Description                              |
| ------------------------ | ------------------------------------------------------- | ---------------------------------------- |
| **Verify XML**           | `.\xml_editor verify -i sample.xml`                     | Checks XML consistency & reports errors. |
| **Fix XML**              | `.\xml_editor verify -i sample.xml -f -o fixed.xml`     | Repairs mismatched/missing tags.         |
| **Format XML**           | `.\xml_editor format -i sample.xml -o formatted.xml`    | Beautifies XML with indentation.         |
| **Minify XML**           | `.\xml_editor mini -i sample.xml -o mini.xml`           | Removes whitespace to reduce size.       |
| **Convert to JSON**      | `.\xml_editor json -i sample.xml -o output.json`        | Converts XML → JSON.                     |
| **Compress XML**         | `.\xml_editor compress -i sample.xml -o out.comp`       | Custom compression (BPE-like).           |
| **Decompress XML**       | `.\xml_editor decompress -i out.comp -o restored.xml`   | Restores full XML.                       |
| **Build Network Graph**  | `.\xml_editor draw -i sample.xml -o graph.jpg`          | Builds graph from users/followers.       |
| **Most Active User**     | `.\xml_editor most_active -i sample.xml`                | User with most outgoing connections.     |
| **Most Influencer User** | `.\xml_editor most_influencer -i sample.xml`            | User with most followers.                |
| **Mutual Followers**     | `.\xml_editor mutual -i sample.xml -ids 1,2,3`          | Common followers.                        |
| **Suggestions**          | `.\xml_editor suggest -i sample.xml -id 1`              | Recommended users to follow.             |
| **Search Posts by Word** | `.\xml_editor search -w word -i sample.xml`            | Writes a list of posts where the word was mentioned. |
| **Search Posts by Topic**| `.\xml_editor search -t topic -i sample.xml`           | Writes a list of posts where the topic was mentioned. |




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

```

- GUI executable is **prebuilt and ready**
- Source code for both CLI and GUI is included
- CLI and GUI share the same processing backend

---
