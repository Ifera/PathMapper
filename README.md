## PathMapper

A data structures project utilizing Dijkistra algorithm and AdjacencyList to find the shortest path between two nodes.

## Overview

**PathMapper** - An end semester project for **EC-200 Data Structure** course. <br /><br />
We were told to make use of what we had learned of Data Structures over the course of the semester and make a program that had the following features:

- Map shortest path between two cities (inter-city).
- Map shortest path between two towns within a city (intra-city).
- Map shortest path between two cities while visiting a particular city i.e. from city A to city C via city B.
- The path should be based on either shortest **time taken** or shortest **distance required**.

We were also made to find the time complexity of the entire project. <br />
All the requirements of the project were fulfilled with homegrown Adjancency List and Dijkistra algorithm.

## Layout

The project is essentially divided into three main classes, namely `AdjacencyList`, `App` and `Program`.

- `AdjacencyList` is the main class here since it handles the creation of vertex, edges and mapping out the smallest path.
- `App` class, wraps over the `AdjacencyList` and provides functions for ease of use.
- `Program` class is responsible for running the entire project.

The project could very well work by just using the `AdjacencyList` class.

## Dataset

For this project to work, it needs a file called `dataset.json`. It essentially contains the record of all the cities, towns, the distances between them and the time taken to reach a certain town. For easier testing a `dataset.json` file has been attached with this project which contains a list of some major cities and towns of Pakistan. Furthermore, a file called `dataset.json.example` is also provided for easier understanding.

## Dependency

This project uses the [nlohmann.json](https://www.nuget.org/packages/nlohmann.json/) package for handling `.json` files. <br />
Do remember to include it (if not included) to the project. More info on how to include a package to Visual Studio 2019 can be found [here](https://docs.microsoft.com/en-us/nuget/quickstart/install-and-use-a-package-in-visual-studio).

## Building and Running

After the dependency has been added, simply open the project in Visual Studio 2019 and click the run icon in the toolbar. Visual Studio will build the project and run it for you.

## Outputs

An example of outputs that can be expected can be seen [here](https://github.com/Ifera/PathMapper/blob/master/meta/Output.pdf).
