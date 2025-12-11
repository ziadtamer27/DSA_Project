---

# XML Editor & Social Network Analyzer

A desktop application (CLI + GUI) for parsing, visualizing, and analyzing XML files that describe a social-network–like dataset.
The project supports XML correction, formatting, conversion to JSON, compression, graph generation, and network analysis features.

---

## 🚀 Features

### **1. Command Line Interface (CLI)**

Run the program using the `xml_editor` command with different operations:

| Operation            | Command Example                                    | Description                                 |
| -------------------- | -------------------------------------------------- | ------------------------------------------- |
| Verify XML           | `xml_editor verify -i input.xml`                   | Validates XML structure and reports errors. |
| Verify & Fix         | `xml_editor verify -i input.xml -f -o fixed.xml`   | Fixes mismatched/missing tags.              |
| Format XML           | `xml_editor format -i input.xml -o formatted.xml`  | Prettifies the XML with indentation.        |
| Convert to JSON      | `xml_editor json -i input.xml -o output.json`      | Converts XML to JSON structure.             |
| Minify XML           | `xml_editor mini -i input.xml -o minified.xml`     | Removes unnecessary whitespace/newlines.    |
| Compress             | `xml_editor compress -i input.xml -o out.comp`     | Compresses XML using a custom algorithm.    |
| Decompress           | `xml_editor decompress -i file.comp -o output.xml` | Restores the compressed file.               |
| Draw Graph           | `xml_editor draw -i input.xml -o graph.jpg`        | Visualizes users and their connections.     |
| Most Active User     | `xml_editor most_active -i input.xml`              | Displays the most connected user.           |
| Most Influencer User | `xml_editor most_influencer -i input.xml`          | Displays the user with most followers.      |
| Mutual Followers     | `xml_editor mutual -i input.xml -ids 1,2,3`        | Shows mutual followers among given IDs.     |
| Suggestions          | `xml_editor suggest -i input.xml -id 1`            | Suggests new accounts to follow.            |
| Search Posts         | `xml_editor search -w word -i input.xml`           | Searches posts containing a word/topic.     |

---

## 🖥️ Graphical User Interface (GUI)

The program also includes a simple, user-friendly GUI that provides:

* Choosing XML files via file browser.
* Viewing input and output text (or first lines for large files).
* Buttons for every operation (verify, format, minify, json, compress, draw graph, etc.).
* Saving outputs to user-selected locations.
* Displaying error highlights for XML inconsistencies.


## 🧠 Data Structures Used

The project uses:

* **Stacks, queues, vectors, linked lists** (allowed STL structures)
* **Custom implementations** for:

  * Trees / XML node structures
  * Graph adjacency list
  * Compression dictionary / encoding structures

All other advanced data structures (tries, maps, sets… etc.) are implemented from scratch as required.

---

## 📊 Graph Representation

Each XML `<user>` node contains:

* `id`
* `name`
* `<posts>`
* `<followers>`

A directed graph is built where:

* Each node represents a user.
* Edge A → B means *A follows B*.

This graph supports all Level 2 operations.

---

## 📉 Compression & Decompression

The program implements a custom compression technique inspired by **Byte Pair Encoding (BPE)** to reduce file size. The compressed output can be fully decompressed to the original XML or JSON.

---

## 🔍 Network Analysis

With the graph constructed, the program can extract:

* Most active user (highest degree)
* Most influential user (most followers)
* Mutual followers between multiple users
* Suggested users to follow based on friend-of-a-friend patterns

---

## 🔎 Post Search

The search engine scans all posts and returns posts that match:

* A specific **word**
* A specific **topic**

Search is available in both CLI and GUI.

---
