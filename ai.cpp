//
//  main.cpp
//  AI_HW_1
//
//  Created by shiyu wang on 9/10/14.
//  Copyright (c) 2014 shiyu wang. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Node
{
	int current;
	int parent;
	int depth;
	string name;
	int cost;
	Node(int a = 0, int b = 0, int c = 0, string name = "")
	{
		current = a;
		parent = b;
		depth = c;
		this -> name = name;
	}
	
 	friend bool operator < (Node x, Node y)
    {
         if(x.cost != y.cost)
              return x.cost > y.cost;
         else
              return x.name > y.name;
    }
};

struct cmp_bfs
{
	bool operator () (Node x, Node y)
	{
		if(x.depth != y.depth)
			return x.depth > y.depth;
		else
			return x.name > y.name;
	}
};

struct cmp_dfs
{
	bool operator () (Node x, Node y)
	{
		if(x.depth != y.depth)
			return x.depth < y.depth;
		else
			return x.name > y.name;
	}
};

struct cmp_ucs
{
	bool operator () (Node x, Node y)
	{
		if(x.cost != y.cost)
			return x.cost > y.cost;
		else
			return x.name > y.name;
	}
}ucs_object;
const int MAX_PEOPLE = 10000;

int type;   //1 bfs 2 dfs 3 uniform-cost
string starting,ending;                
int size;                            
string people[MAX_PEOPLE];
int graph[MAX_PEOPLE][MAX_PEOPLE];     
map<string,int> m;
int i,j;
bool visited[MAX_PEOPLE];
int sum;
int p;
int startIndex,endIndex;
int temp;					
Node temp1;
Node temp2;				//to record the element just popped
bool found;

void init();
void bfs();
void dfs();
void ucs();

int main(int argc, const char * argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	init();
	if(startIndex == -1 || endIndex == -1)
	{
		cout << "NoPathAvailable" << endl;
		return 0;
	}
    if(type == 1)
    {
        //cout << "bfs" << endl;
        bfs();
    }
    else if(type == 2)
    {
		//cout << "dfs" << endl;
        dfs();
    }
    else    //uniform-cost
    {
    	//cout << "usc" << endl;
		ucs();
    }
    return 0;
}

void init()
{
	cin >> type >> starting >> ending >> size;
    for(i = 0; i < size; i++)
    {
        cin >> people[i];
		m[people[i]] = i;
    }
	//look for start point and end point
	startIndex = -1;
	endIndex = -1;
    for(i = 0; i < size; i++)
    {
        if(people[i] == starting)
            startIndex = i;
        if(people[i] == ending)
            endIndex = i;
    }
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            cin >> graph[i][j];
        }
    }
	found = false;
    memset(visited,0,sizeof(visited));
}

void bfs()
{
    priority_queue<Node,vector<Node>,cmp_bfs> q;
	vector<Node> expansion;
	stack<string> path;

	//start bfs
	Node root(startIndex,-1,0,starting);
	q.push(root);
	visited[startIndex] = true;
	while(!q.empty())
	{
		temp1 = q.top();
		temp = temp1.current;
		expansion.push_back(temp1);
		if(temp == endIndex)
		{
			found = true;
			break;
		}
		q.pop();

		for(i = 0; i < size; i++)
		{
			if(graph[temp][i] != 0 && !visited[i])
			{
				visited[i] = true;
				temp2.current = i;
				temp2.parent = temp;
				temp2.name = people[i];
				temp2.depth = temp1.depth + 1;
				q.push(temp2);
			}

		}
	}
	if(!found)
	{
		cout << "NoPathAvailable" << endl;
		return;
	}
	//print expansion
	for(i = 0; i < expansion.size(); i++)
	{
		if(i != expansion.size() - 1)
			cout << people[expansion[i].current] << "-";
		else
			cout << people[expansion[i].current] << endl;
	}
	//print path
	temp2 = expansion[i-1];
	path.push(ending);
	p = temp2.parent;
	//sum is path total cost
	sum = graph[endIndex][p];
	while(p != -1)
	{
		for(i = 0; i < expansion.size(); i++)
		{
			if(expansion[i].current == p)
			{
				path.push(people[expansion[i].current]);
				p = expansion[i].parent;
				if(p != -1)
					sum += graph[expansion[i].current][p];
			}
		}
	}
	while(!path.empty())
	{
		if(path.top() != ending)
		{
			cout << path.top() << "-";
			path.pop();
		}
		else
		{
			cout << path.top() << endl;
			path.pop();
		}
	}
	cout << sum << endl;
}

void dfs()
{
    priority_queue<Node,vector<Node>,cmp_dfs> q;
	vector<Node> expansion;
	stack<string> path;

	//start dfs
	Node root(startIndex,-1,0,starting);
	q.push(root);
	visited[startIndex] = true;
	while(!q.empty())
	{
		temp1 = q.top();
		temp = temp1.current;
		expansion.push_back(temp1);
		if(temp == endIndex)
		{
			found = true;
			break;
		}
		q.pop();

		for(i = 0; i < size; i++)
		{
			if(graph[temp][i] != 0 && !visited[i])
			{
				visited[i] = true;
				temp2.current = i;
				temp2.parent = temp;
				temp2.name = people[i];
				temp2.depth = temp1.depth + 1;
				q.push(temp2);
			}

		}
	}
	if(!found)
	{
		cout << "NoPathAvailable" << endl;
		return;
	}
	//print expansion
	for(i = 0; i < expansion.size(); i++)
	{
		if(i != expansion.size() - 1)
			cout << people[expansion[i].current] << "-";
		else
			cout << people[expansion[i].current] << endl;
	}
	//print path
	temp2 = expansion[i-1];
	path.push(ending);
	p = temp2.parent;
	//sum is path total cost
	sum = graph[endIndex][p];
	while(p != -1)
	{
		for(i = 0; i < expansion.size(); i++)
		{
			if(expansion[i].current == p)
			{
				path.push(people[expansion[i].current]);
				p = expansion[i].parent;
				if(p != -1)
					sum += graph[expansion[i].current][p];
			}
		}
	}
	while(!path.empty())
	{
		if(path.top() != ending)
		{
			cout << path.top() << "-";
			path.pop();
		}
		else
		{
			cout << path.top() << endl;
			path.pop();
		}
	}
	cout << sum << endl;
}

void ucs()
{
    priority_queue<Node,vector<Node>,cmp_ucs> q;
	vector<Node> expansion;
	vector<Node> open;
	stack<string> path;
	bool closed[MAX_PEOPLE];

	memset(closed,false,sizeof(closed));

	
	//cout << "haha" << endl;
	int par_cost;
	//start ucs
	Node root(startIndex,-1,0,starting);
	root.cost = 0;
	q.push(root);
	visited[startIndex] = true;
	int iter = 0;
	while(!q.empty())
	{
		//cout << iter++ << endl;
		temp1 = q.top();
		temp = temp1.current;
		par_cost = temp1.cost;
		expansion.push_back(temp1);
		closed[temp] = true;
		if(temp == endIndex)
		{
			found = true;
			//temp1.parent = expansion.back().current;
			//cout << temp1.current;
			break;
		}
		
		q.pop();
		//open.clear();

		for(i = 0; i < size; i++)
		{
			if(graph[temp][i] != 0 && !closed[i] && !visited[i])
			{
				visited[i] = true;
				temp2.current = i;
				temp2.parent = temp;
				temp2.name = people[i];
				temp2.cost = graph[temp][i] + par_cost;
				//cout << people[i] <<"\'s parent is "<< people[temp] << " cost to root is " << temp2.cost << endl; 
				q.push(temp2);
				//open.push_back(temp2);
			}
			else if(graph[temp][i] != 0 && !closed[i] && visited[i])
			{
				//更新到根的距离
				//cout << iter << endl;
				set<Node> myset;
				myset.clear();
				while(1)
				{
					//cout << "aaaaaa" << endl;
					temp1 = q.top();
					if(temp1.current != i)			//这里出现了问题，有可能一直进出的都是一个元素，因为这是一个优先队列，而不是一个普通队列
					{
						q.pop();
						myset.insert(temp1);
					}
					else
					{
						if(par_cost + graph[temp][i] < temp1.cost)
						{
							//cout << "fuck" << endl;
							temp1.cost = par_cost + graph[temp][i];
							temp1.parent = temp;
							q.pop();
							q.push(temp1);
						}
						break;
					}
				}
				//把元素S重新加入优先队列
				set<Node>::iterator it;
				for(it = myset.begin(); it != myset.end(); it++)
				{
					q.push(*it);
				}	
			}
		}
		//sort(open.begin(),open.end(),ucs_object);
		//q.push(open.front());
	}
	if(!found)
	{
		cout << "NoPathAvailable" << endl;
		return;
	}
	//print expansion
	for(i = 0; i < expansion.size(); i++)
	{
		if(i != expansion.size() - 1)
			cout << people[expansion[i].current] << "-";
		else
			cout << people[expansion[i].current] << endl;
	}
	//print path
	temp2 = expansion[i-1];
	path.push(ending);
	p = temp2.parent;
	//cout << people[p] << endl;
	//sum is path total cost
	sum = graph[endIndex][p];
	while(p != -1)
	{
		for(i = 0; i < expansion.size(); i++)
		{
			if(expansion[i].current == p)
			{
				path.push(people[expansion[i].current]);
				p = expansion[i].parent;
				if(p != -1)
					sum += graph[expansion[i].current][p];
			}
		}
	}
	while(!path.empty())
	{
		if(path.top() != ending)
		{
			cout << path.top() << "-";
			path.pop();
		}
		else
		{
			cout << path.top() << endl;
			path.pop();
		}
	}
	cout << sum << endl;
}

