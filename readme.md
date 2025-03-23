# Maximum Clique Algorithm Implementation

This repository contains C++ implementations of maximum clique algorithms and datasets for testing. The algorithms provided are:

- tomita.cpp (Tomita's Algorithm)
- bron.cpp (Bron-Kerbosch Algorithm)
- chibo.cpp (Chiba and Nishizeki Algorithm)

The datasets available are:

- Wiki-Vote.txt
- Email-Enron.txt
- as-skitter.txt

This repository also contains a C++ file to preprocess Wiki-Vote.txt and convert it to wiki_processed.txt

## Prerequisites

Ensure you have a C++ compiler installed (e.g., g++).

### Datasets

- The datasets are formatted as text files.
- Ensure that the datasets are correctly placed in the repository directory before execution.

## Compilation

sh
g++ preprocess.cpp -o preprocess
./preprocess

Each algorithm needs to be compiled separately before execution. Use the following commands to compile them:

sh
g++ tomita.cpp -O9 -o tomita
g++ bron.cpp -O9 -o bron
g++ chibo.cpp -O9 -o chibo

## Execution

After compilation, run each algorithm sequentially on all three datasets:

For tomita.cpp and bron.cpp, first preprocess the file Wiki-Vote.txt by just running preprocess.cpp, this will generate wiki_processed.txt

sh
./tomita wiki_processed.txt
./bron wiki_processed.txt
./chibo Wiki-Vote.txt

./tomita Email-Enron.txt
./bron Email-Enron.txt
./chibo Email-Enron.txt

./tomita as-skitter.txt
./bron as-skitter.txt
./chibo as-skitter.txt

# Website Link

The website can be found in the following url: https://maximalclique.streamlit.app/

# Individual Contributions

## Prahlad Ponnatata(2022A7PS0097H) - chibo.cpp

Arboricity and Subgraph Listing Algorithms
Also primarily made the webpage.

## Sai Ashish Vure(2022A7PS0016H) - bron.cpp and preprocessing.cpp

Listing All Maximal Cliques in Sparse Graphs in Near-optimal Time

## Nikhilesh Balla(2022A7PS0097H) - tomita.cpp

The worst-case time complexity for generating all maximal cliques and computational experiments.

## all 3 of us worked on the report and other deliverables
