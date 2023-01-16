// graph.h

#ifndef GRAPH_H
#define GRAPH_H

//------------------------------------------------------------PACKAGES----------------------------------------------------------------------

#include "LinkedList.h"
#include <string.h>
#include <Arduino.h>

//------------------------------------------------------------CLASSES-----------------------------------------------------------------------

using GenVoidFunct = void (*)();
using GenBoolFunct = bool (*)();
using Node = String;

class Action {
  private:
    GenVoidFunct do_function;
    GenBoolFunct stop_function;
  public:
    Action(GenVoidFunct f_void, GenBoolFunct f_int);
    GenVoidFunct getDoFunction();
    GenBoolFunct getStopFunction();
    void setDoFunction(GenVoidFunct f_void);
    void setStopFunction(GenBoolFunct f_int);
    bool execAction();
    void print();
};

class Arc {
  private:
    Node start_node;
    Node end_node;
    LinkedList<Action> cost;
  public:
    Arc();
    Arc(Node n1, Node n2, LinkedList<Action> c);
    Node getStartNode();
    Node getEndNode();
    LinkedList<Action> getCost();
    void setStartNode(Node n1);
    void setEndNode(Node n2);
    bool execCost();
    void print();
};

class Graph {
  private:
    LinkedList<Node> nodes;
    LinkedList<Arc> arcs;
  public:
    Graph();
    Graph(LinkedList<Node> nodes, LinkedList<Arc> arcs);
    LinkedList<Node> getNodes();
    LinkedList<Arc> getArcs();
    void setNodes(LinkedList<Node> list_nodes);
    void setArcs(LinkedList<Arc> list_arcs);
    LinkedList<Arc> get_arcs_by_start_node(Node start_node);
    LinkedList<Arc> get_arcs_by_end_node(Node end_node);
    LinkedList<Arc> get_path(Node start_node, Node end_node);
    void print();
};

//------------------------------------------------------------TYPE_DEF-------------------------------------------------------------------------

// typedef void* (*gen_function)(void*);

// typedef struct Action {
//   gen_function do_func;
//   gen_function stop_func;
// } Action;

// typedef char* Node;

// typedef struct Arc {
//   Node n_i;
//   Node n_f;
//   Action* transitions;
// } Arc;

//------------------------------------------------------------ACTIONS-----------------------------------------------------------------------

Action::Action(GenVoidFunct f_void, GenBoolFunct f_int)
{
  do_function = f_void;
  stop_function = f_int;
}

GenVoidFunct Action::getDoFunction()
{
  return do_function;
}

GenBoolFunct Action::getStopFunction()
{
  return stop_function;
}

void Action::setDoFunction(GenVoidFunct f_void)
{
  do_function = f_void;
}

void Action::setStopFunction(GenBoolFunct f_int)
{
  stop_function = f_int;
}

bool Action::execAction()
{
  do_function();
  return stop_function();
}

void Action::print()
{
  Serial.print("(");
  Serial.print((unsigned int)do_function, HEX);
  Serial.print(", ");
  Serial.print((unsigned int)stop_function, HEX);
  Serial.print(")");
  Serial.print("\n");
}

//------------------------------------------------------------ARCS---------------------------------------------------------------------------

Arc::Arc()
{

}

Arc::Arc(Node n1, Node n2, LinkedList<Action> c)
{
  start_node = n1;
  end_node = n2;
  cost = c;
}

Node Arc::getStartNode()
{
  return start_node;
}

Node Arc::getEndNode()
{
  return end_node;
}

LinkedList<Action> Arc::getCost()
{
  return cost;
}

void Arc::setStartNode(Node n1)
{
  start_node = n1;
}

void Arc::setEndNode(Node n2)
{
  end_node = n2;
}

void Arc::print()
{
  Serial.print("\n\tNodes : (");
  Serial.print(start_node);
  Serial.print(", ");
  Serial.print(end_node);
  Serial.print(")\n");
  Serial.print("\tCost : [");
  if(cost.getLength() > 0)
  {
    cost.moveToStart();
    do {
      cost.getCurrent().print();
      Serial.print(", ");
    } while(cost.next());
    Serial.print("]\n");
    cost.moveToStart();
  }
}

//------------------------------------------------------------GRAPHS---------------------------------------------------------------------------

Graph::Graph()
{
  nodes = LinkedList<Node>();
  arcs = LinkedList<Arc>();
}

Graph::Graph(LinkedList<Node> node_list, LinkedList<Arc> arc_list) {
  nodes = node_list;
  arcs = arc_list;
}

LinkedList<Node> Graph::getNodes()
{
  return nodes;
}

LinkedList<Arc> Graph::getArcs()
{
  return arcs;
}

void Graph::setNodes(LinkedList<Node> list_nodes)
{
  nodes = list_nodes;
}

void Graph::setArcs(LinkedList<Arc> list_arcs)
{
  arcs = list_arcs;
}

LinkedList<Arc> Graph::get_arcs_by_start_node(Node start_node)
{
  LinkedList<Arc> arc_list = LinkedList<Arc>();
  arcs.moveToStart();
  do
  {
    if(arcs.getCurrent().getStartNode() == start_node)
    {
      arc_list.Append(arcs.getCurrent());
    }
  } while(arcs.next());
  arcs.moveToStart();
  return arc_list;
}

LinkedList<Arc> Graph::get_arcs_by_end_node(Node end_node)
{
  LinkedList<Arc> arc_list = LinkedList<Arc>();
  arcs.moveToStart();
  do
  {
    if(arcs.getCurrent().getEndNode() == end_node)
    {
      arc_list.Append(arcs.getCurrent());
    }
    arcs.next();
  } while(arcs.next());
  arcs.moveToStart();
  return arc_list;
}

LinkedList<Arc> Graph::get_path(Node s_node, Node e_node)
{
  //std::cout << "get_path(" << s_node << ", " << e_node << ")" << std::endl;
  LinkedList<Arc> path = LinkedList<Arc>();
  LinkedList<Arc> s_node_arcs = get_arcs_by_start_node(s_node);
  if (s_node_arcs.getLength() > 0)
  {
    do
    {
      Arc arc = s_node_arcs.getCurrent();
      //std::cout << "\nCurrent : "; arc.print();
      // arrived at final arc
      if (arc.getEndNode() == e_node)
      {
        //std::cout << "\nEnd Arc found" << std::endl;
        path.Append(arc);
        break;
      }
    } while (s_node_arcs.next());
    s_node_arcs.moveToStart();
    // arcs between
    if (path.getLength() == 0) {
      do
      {
        Arc arc = s_node_arcs.getCurrent();
        LinkedList<Arc> child_arcs = get_path(arc.getEndNode(), e_node);
        if (child_arcs.getLength() > 0)
        {
          path.Append(arc);
          path = path + child_arcs;
        }
      } while (s_node_arcs.next());
    }
  }
  // closed way
  return path;
}

void Graph::print()
{
	Serial.print("\nn* Nodes : ");
  Serial.print(nodes.getLength());
	Serial.print("\nn* Arcs : ");
  Serial.print(arcs.getLength());
  if(arcs.getLength() > 0)
  {
    arcs.moveToStart();
    do
    {
      arcs.getCurrent().print();
    } while(arcs.next());
    arcs.moveToStart();
  }
}

#endif
