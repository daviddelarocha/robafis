// airport_graph.h

#ifndef AIRPORTGRAPH_H
#define AIRPORTGRAPH_H

//------------------------------------------------------------PACKAGES----------------------------------------------------------------------

#include "graph.h"
#include "LinkedList.h"
#include "controls.h"

//------------------------------------------------------------GRAPH_DEFINITION---------------------------------------------------------------

// converstion functions
template <size_t N>
Action* getActionArray(const Action (&a)[N])
{
  return a;
}

LinkedList<Node> init_nodes()
{
  // Nodes declaration
  int size = 14;
  Node node_list[size] = {
    "P0",
    "N6",
    "N6p",
    "N8",
    "N8p",
    "M8",
    "M8p",
    "M10",
    "M10p",
    "M11",
    "M11p",
    "P1",
    "P2",
    "P3",
  };
  LinkedList<Node> node_linkedlist(node_list, size);

  return node_linkedlist;
}

LinkedList<Arc> init_arcs_arrimage()
{
  // Arcs-list declaration
  LinkedList<Arc> arc_list = LinkedList<Arc>();
  LinkedList<Action> action_list = LinkedList<Action>();
  
  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_JAUNE));
  // Append Arc to list
  Arc arc = Arc("P0", "N6", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_JAUNE));
  // Append Arc to list
  arc = Arc("P0", "N8", action_list);
  arc_list.Append(arc);
  action_list.Clear();
  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES, &DETECT_JAUNE));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_JAUNE));
  // Append Arc to list
  arc = Arc("P0", "M8", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_JAUNE));
  arc = Arc("P0", "M10", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_JAUNE));
  arc = Arc("P0", "M11", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_JAUNE));
  arc = Arc("N8", "M8", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  return arc_list;
}

LinkedList<Arc> init_arcs_desarrimage()
{
  // Arcs-list declaration
  LinkedList<Arc> arc_list = LinkedList<Arc>();
  LinkedList<Action> action_list = LinkedList<Action>();

  // E -> E'
  // Appending Actions
  action_list.Append(Action(&TAKE_PLANE, &true_flag));
  Arc arc = Arc("N6", "N6p", action_list);
  arc_list.Append(arc);
  // arc = Arc("N8", "N8p", action_list);
  // arc_list.Append(arc);
  // arc = Arc("M8", "M8p", action_list);
  // arc_list.Append(arc);
  // arc = Arc("M10", "M10p", action_list);
  // arc_list.Append(arc);
  // arc = Arc("M11", "M11p", action_list);
  // arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_BLEU));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  arc = Arc("M8p", "N8p", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("N6p", "P1", action_list);
  arc_list.Append(arc);
  // arc = Arc("N8p", "P2", action_list);
  // arc_list.Append(arc);
  // arc = Arc("M10p", "P3", action_list);
  // arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_DROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("N6p", "P2", action_list);
  arc_list.Append(arc);
  action_list.Clear();
  // arc = Arc("N8p", "P3", action_list);
  // arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_DROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("N6p", "P3", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&VIRAGE_DROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("N8p", "P1", action_list);
  arc_list.Append(arc);
  action_list.Clear();
  // arc = Arc("M10p", "P2", action_list);
  // arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&VIRAGE_DROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("M10p", "P1", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("M11p", "P3", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("M11p", "P2", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_TTDROITE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_VERT));
  action_list.Append(Action(&VIRAGE_GAUCHE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNES_SLOW, &DETECT_ROUGE));
  arc = Arc("M11p", "P1", action_list);
  arc_list.Append(arc);
  action_list.Clear();

  // Appending Actions
  action_list.Append(Action(&LEAVE_PLANE, &true_flag));
  action_list.Append(Action(&SUIVI_LIGNE, &DETECT_ROUGE));
  action_list.Append(Action(&AVANCE_PTPEU, &true_flag));
  arc = Arc("P1", "P0", action_list);
  arc_list.Append(arc);
  // arc = Arc("P2", "P0", action_list);
  // arc_list.Append(arc);
  // arc = Arc("P3", "P0", action_list);
  // arc_list.Append(arc);
  action_list.Clear();

  return arc_list;
}

Graph init_airport_graph()
{
  // init graph with Nodes + Arcs
  Graph graph(init_nodes(), init_arcs_arrimage() + init_arcs_desarrimage());

  return graph;
}

LinkedList<Node> map_nodes(Node start_node, Node end_node)
{
  if(
    (start_node == "N8" && end_node == "N8p") ||
    (start_node == "M8" && end_node == "M8p") ||
    (start_node == "M10" && end_node == "M10p") ||
    (start_node == "M11" && end_node == "M11p")
  )
  {
    start_node = "N6";
    end_node = "N6p";
  }
  else if(
    (start_node == "N8p" && end_node == "P2") ||
    (start_node == "M10p" && end_node == "P3")
  )
  {
    start_node = "N6p";
    end_node = "P1";
  }
  else if(
    (start_node == "N8p" && end_node == "P3")
  )
  {
    start_node = "N6p";
    end_node = "P2";
  }
  else if(
    (start_node == "M10p" && end_node == "P2")
  )
  {
    start_node = "N8p";
    end_node = "P1";
  }
  else if(
    (start_node == "P2" && end_node == "P0") ||
    (start_node == "P3" && end_node == "P0")
  )
  {
    start_node = "P1";
    end_node = "P0";
  }

  LinkedList<Node> mapped_nodes = LinkedList<Node>();
  mapped_nodes.Append(start_node);
  mapped_nodes.Append(end_node);

  return mapped_nodes;
}

#endif




