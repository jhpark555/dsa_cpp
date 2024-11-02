#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <functional>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <list>
#include <queue>

using namespace std;

struct Vertex;
struct Edge
{
    Vertex *dest;
    double cost;
    Edge(Vertex *d=NULL, double c=0.0) : dest(d), cost(c) {}
};

struct Vertex
{
    string name;
    vector<Edge> adj;
    double dist;
    Vertex *prev;
    int scratch;

    Vertex(const string &nm) : name(nm)
        { reset();  }
    void reset()
       { dist = INFINITY; prev=NULL; scratch=0; }

};

// Structure stored in priority queue for Dijkstra's algorithm.
struct Path
{
    Vertex *dest;   // w
    double  cost;   // d(w)

    Path( Vertex *d = 0, double c = 0.0 )
      : dest( d ), cost( c ) { }

    bool operator> ( const Path & rhs ) const
      { return cost > rhs.cost; }
    bool operator< ( const Path & rhs ) const
      { return cost < rhs.cost; }
};

class Graph
{
    public:
        Graph() {}
        ~Graph();

        void addEdge( const string & sourceName, const string & destName, double cost );
        void printPath( const string & destName ) const;
        void unweighted( const string & startName );
        void dijkstra( const string & startName );
        void dijkstra2( const string & startName );   // Chapter 23
        void negative( const string & startName );
        void acyclic( const string & startName );

    private:
        Vertex * getVertex( const string & vertexName );
        void printPath( const Vertex & dest ) const;
        void clearAll( );

        typedef map<string,Vertex *,less<string> > vmap;

        // Copy semantics are disabled; these make no sense.
        Graph( const Graph & rhs ) { }
        const Graph & operator= ( const Graph & rhs )
          { return *this; }

        vmap vertexMap;
};

Graph::~Graph()
{
    for(vmap::iterator itr=vertexMap.begin();
       itr!= vertexMap.end(); ++itr)
       delete itr->second;
}

Vertex *Graph::getVertex(const string &vertexName)
{
    vmap::iterator itr =vertexMap.find(vertexName);

    if(itr == vertexMap.end())
    {
        Vertex *newv=new Vertex(vertexName);
        vertexMap[vertexName]= newv;
        return newv;
    }
    return itr->second;
}

void Graph::addEdge(const string &sourceName,const string & destName
        , double cost) 
{
    Vertex *v= getVertex(sourceName);
    Vertex *w= getVertex(destName);
    v->adj.push_back(Edge(w,cost));
}
void Graph::clearAll()
{
    for(vmap::iterator itr=vertexMap.begin();
        itr !=vertexMap.end(); ++itr)
        itr->second->reset();
}

void Graph::printPath(const Vertex &dest) const
{
    if(dest.prev !=NULL)
    {
        printPath(*dest.prev);
        cout<<" to ";
    }
    cout<< dest.name;
}
void Graph::printPath(const string &destName) const
{
    vmap::const_iterator itr =vertexMap.find(destName);
    if(itr == vertexMap.end())
        cout<<" Not found";

    const Vertex &w = *(itr->second);
    if(w.dist ==INFINITY)
        cout<<destName<< " is unreachable";
    else
    {
        cout<<"Cost is: "<<w.dist <<") ";
        printPath(w);
    }
    cout<< endl;
}

// Single-source negative weighted shortest-path algorithm.
void Graph::negative( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        cout<< " is not a vertex in this graph" ;

    clearAll( );
    Vertex *start = itr->second;
    list<Vertex *> q;
    q.push_back( start ); start->dist = 0; start->scratch++;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( ); q.pop_front( );
        if( v->scratch++ > 2 * vertexMap.size( ) )
            cout<< "Negative cycle detected" ;

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
                  // Enqueue only if not already on the queue
                if( w->scratch++ % 2 == 0 )
                    q.push_back( w );
                else
                    w->scratch--;   // undo the push
            }
        }
    }
}

void Graph::unweighted(const string & startName)
{
    vmap::iterator itr=vertexMap.find(startName);
    if(itr ==vertexMap.end())
        cout<<" is not a Vertex";
    clearAll();
    Vertex *start = itr->second;
    list<Vertex *> q;
    q.push_back(start);
    start->dist=0;

    while( !q.empty())
    {
        Vertex *v=q.front();
        q.pop_front();

        for( int i=0; i< v->adj.size(); i++)
        {
            Edge e= v->adj[i];
            Vertex *w=e.dest;
            if(w->dist == INFINITY)
            {
                w->dist =v->dist+1;
                w->prev=v;
                q.push_back(w);
            }
        }
    }
}

void Graph::dijkstra(const string &startName)
{
    priority_queue<Path, vector<Path>, greater<Path>> pq;
    Path vrec; 

    vmap::iterator itr= vertexMap.find(startName);
    if(itr ==vertexMap.end()) 
        cout<<"is not a vertex";

    clearAll();
    Vertex *start=itr->second;
    pq.push(Path(start,0));
    start->dist=0;

    
    for(int nodesSeen=0; nodesSeen< vertexMap.size(); nodesSeen++)
    {
        do
        {
            if(pq.empty())
                return;
            vrec=pq.top(); pq.pop();
        } while( vrec.dest->scratch !=0);
        
        Vertex *v = vrec.dest;
        v->scratch = 1;

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( cvw < 0 )
                cout<<"Graph has negative edges" ;

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
                pq.push( Path( w, w->dist ) );
            }
        }
    }
}

// Process a request; return false if end of file.
bool processRequest( istream & in, Graph & g )
{
    string startName;
    string destName;

    cout << "Enter start node: ";
    if( !( in >> startName ) )
        return false;
    cout << "Enter destination node: ";
    if( !( in >> destName ) )
        return false;

    //g.negative( startName );
    g.unweighted(startName);
    g.printPath( destName );

   
    return true;
}

// Single-source weighted shortest-path algorithm for acyclic graphs.
void Graph::acyclic( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
        cout<<" is not a vertex in this graph" ;

    clearAll( );
    Vertex *start = (*itr).second;
    list<Vertex *> q;
    start->dist = 0;

      // Compute the indegrees
    for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        Vertex *v = (*itr).second;
        for( int i = 0; i < v->adj.size( ); i++ )
            v->adj[ i ].dest->scratch++;
    }

      // Enqueue vertices of indegree zero
    for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        Vertex *v = (*itr).second;
        if( v->scratch == 0 )
            q.push_back( v );
    }

    int iterations;
    for( iterations = 0; !q.empty( ); iterations++ )
    {
        Vertex *v = q.front( );	q.pop_front( );

        for( int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( --w->scratch == 0 )
                q.push_back( w );

            if( v->dist == INFINITY )
                continue;

            if( w->dist > v->dist + cvw )
            {
                w->dist = v->dist + cvw;
                w->prev = v;
            }
        }
    }

    if( iterations != vertexMap.size( ) )
        cout<< "Graph has a cycle!" ;
}


int main( int argc, char *argv[ ] )
{
    Graph g;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " graphfile" << endl;
        return 1;
    }

    ifstream inFile( argv[ 1 ] );
    if( !inFile )
    {
        cerr << "Cannot open " << argv[ 1 ] << endl;
        return 1;
    }

    cout << "Reading file... " << endl;

    string oneLine;

      // Read the edges; add them to g
    while( !getline( inFile, oneLine ).eof( ) )
    {
        string source, dest;
        double cost;

        istringstream st( oneLine );


        st >> source; st >> dest; st >> cost;
        if( st.fail( ) )
            cerr << "Bad line: " << oneLine << endl;
        else
            g.addEdge( source, dest, cost );
    }

    cout << "File read" << endl << endl;
    while( processRequest( cin, g ) )
        ;

    return 0;
}


