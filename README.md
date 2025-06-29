# Hyderabad Metro Shortest-Path Solver

A C++ command-line application to compute the shortest path (in terms of number of hops) between any two stations in the Hyderabad Metro network using Dijkstra’s algorithm.

## Features

* **Full Hyderabad Metro Coverage**: Models all current stations (Miyapur to Sultan Bazaar) and interchanges.
* **Dijkstra’s Algorithm**: Efficiently computes shortest-hop routes using a min-heap (O(E log V)).
* **User-Friendly I/O**: Lists stations with indices, accepts source and destination by exact station name, and prints both distance and route.
* **Extensible**: Easily add or update station connections by editing `connect` and `connect_range` calls in `main.cpp`.

## Prerequisites

* **C++17** compiler (e.g., `g++`, `clang++`)
* Standard C++ libraries

## Building

```bash
# Compile the application
g++ -std=c++17 -O2 main.cpp -o hyderabad_metro
```

## Usage

1. Run the binary:

   ```bash
   ./hyderabad_metro
   ```
2. The program will list all stations with their indices.
3. Enter the **source** station name exactly as displayed.
4. Enter the **destination** station name exactly as displayed.
5. The application outputs:

   * The minimum number of hops between the two stations.
   * The ordered list of stations along the shortest path.

### Example

```text
Stations:
  1: Miyapur
  2: JNTU College
  …
 56: Sultan Bazaar

Enter source station name (exactly as shown): Miyapur
Enter destination station name: Ameerpet

Shortest hops from "Miyapur" to "Ameerpet": 10

Route:
  - Miyapur
  - JNTU College
  - KPHB Colony
  - Kukatpally
  - Dr. B.R. Ambedkar Balanagar
  - Moosapet
  - Bharat Nagar
  - Erragadda
  - ESI Hospital
  - S.R. Nagar
  - Ameerpet
```

## Customizing the Network

* \`\`\*\* vector\*\* in `main.cpp`: Contains the list of station names (1-based index). Update if new stations are added.
* \`\`: Defines a bidirectional edge between station indices `x` and `y` with weight 1.
* \`\`: Shortcut to connect consecutive indices from `start` to `end + 1`.

Simply modify or add these calls to reflect any changes in the metro network.

## License

This project is released under the MIT License. Feel free to reuse and adapt.
