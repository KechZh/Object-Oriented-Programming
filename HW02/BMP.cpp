#include<bits/stdc++.h>
using namespace std;
default_random_engine generator;
uniform_real_distribution<double> dis(0,1);
int seed;
class request{
private:
    int id;
    bool match=false;
    int resourceid;
    double weight;
public:
    void input_id(int request_id){
        id=request_id;
    }
    void random_weight(){
        weight=dis(generator);
    }
    int get_id(){
        return id;
    }
    bool get_match(){
        return match;
    }
    int get_resourceid(){
        return resourceid;
    }
    double get_weight(){
        return weight;
    }
    friend class resource;
};
class resource{
private:
    int id;
    bool match=false;
    int requestid;
public:
    static int ans;
    void input_id(int resource_id){
        id=resource_id;
    }
    int get_id(){
        return id;
    }
    bool get_match(){
        return match;
    }
    bool operator->* (request &b){
        if(!match&&!b.match){
            match=b.match=true;
            b.resourceid=id;
            requestid=b.id;
            return true;
        }
        else
            return false;
    }
};
int resource::ans=0;
int main(int argc,char *argv[]){
    seed=atoi(argv[1]);
    generator.seed(seed);
    freopen("request.txt","r",stdin);
	freopen("result.txt","w",stdout);
    vector<request> req;
    vector<resource> res;
    int graph[100][100];
    int time_slot;
    memset(graph,0,sizeof(graph));
    cin>>time_slot;
    while(time_slot--){
        int time_id,num_request,num_resource,num_edge;
        cin>>time_id>>num_request>>num_resource;
        while(num_request--){
            request temp;
            int id;
            cin>>id;
            temp.input_id(id);
            temp.random_weight();
            req.push_back(temp);
        }
        while(num_resource--){
            resource temp;
            int id;
            cin>>id;
            temp.input_id(id);
            res.push_back(temp);
        }
        cin>>num_edge;
        while(num_edge--){
            int edge_id,request_id,resourse_id;
            cin>>edge_id>>request_id>>resourse_id;
            graph[request_id][resourse_id]=1;
        }
        for(int i=0;i<res.size();i++){
            if(res[i].get_match())
                continue;
            int resource_id=res[i].get_id();
            int max_node=-1;
            double max_weight=-1;
            for(int j=0;j<req.size();j++){
                if(req[j].get_match())
                    continue;
                int request_id=req[j].get_id();
                if(graph[request_id][resource_id]&&req[j].get_weight()>max_weight){
                    max_weight=req[j].get_weight();
                    max_node=j;
                }
            }
            if(max_node!=-1&&res[i]->*req[max_node])
                resource::ans++;
        }
    }
    cout<<resource::ans<<endl;
    for(int i=0;i<req.size();i++)
        if(req[i].get_match())
            cout<<req[i].get_id()<<" "<<req[i].get_resourceid()<<endl;
    return 0;
}

