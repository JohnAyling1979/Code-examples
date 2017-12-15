#ifndef ASSIGNMENT9_H
#define ASSIGNMENT9_H
#include <vector>
#include <list>
#include <utility>//for pair

class graph {
    private:
	//added order,edges, and counter as
	//private varibles over using globle ones
	std::vector<int> order;
	std::vector<std::pair<int,int> > edges;
	int counter;
        int size;
        std::vector< std::list<int> > adj_list;
        std::vector< char > labels;
        void depth_first( int );
    public:
        graph( const char* filename );
        ~graph();
        int get_size() const;
        void traverse( ) ;
        void print ( ) const;
        void topological();//testing
};

#endif
