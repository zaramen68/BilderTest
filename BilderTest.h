
#pragma once

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <map>
#include <thread>
#include <exception>
#include <stdexcept>


struct Target {
	Target(size_t id_, std::function<void()> task_, std::vector<int> adj_targets_) :id(id_), task(task_), adj_targets(adj_targets_) { state = 0; }
	size_t id;
	std::function<void()> task;
	std::vector<int> adj_targets;
	int state;
	void set_state(int state_) { state = state_; }
};


class BuildGraph {
public:
	BuildGraph(const std::map<int, std::shared_ptr<Target>> &target_list) {
		dim = target_list.size();
		no_loop = false;
		v_graph.resize(dim);
		adj_matrix.resize(dim);
		for (int i = 0; i < dim; ++i) {
			adj_matrix[i].resize(dim);
		}
		for (int i = 0; i < dim; ++i) {
			v_graph[i] = target_list.at(i+1);
			
			int zero_flag = 0;
			for (int item : target_list.at(i+1)->adj_targets) {
				adj_matrix[i][item-1] = 1;
				adj_matrix[item-1][i] = -1;
				++zero_flag;
			}
			if (zero_flag > 0) { no_loop = true; }
		}
	}

	const std::vector<std::vector<int>> get_matrix() const {
		return adj_matrix;
	}
	const std::vector < std::shared_ptr<Target>>  get_graph() const {
		return v_graph;
	}

	const bool  is_loop() const {
		return no_loop;
	}

	const int get_dim() const {
		return dim;
	}

private:
	int dim;
	bool no_loop;
	std::vector<std::vector<int>> adj_matrix;
	
	std::vector<std::shared_ptr<Target>> v_graph;
};


void make_task(std::shared_ptr<Target> target) {
	target->task();
	target->set_state(3);
}

class Builder {
public:
	explicit Builder(size_t num_threads) {}



	void execute(const BuildGraph& build_graph, size_t target_id) {
		if (!build_graph.is_loop()) { 
			throw "Loop in graph";
		 }
		int dim = build_graph.get_dim();
		std::vector<std::shared_ptr<Target>> nodes = build_graph.get_graph();
		std::vector<std::vector<int>> adj_matrix = build_graph.get_matrix();
		
		std::vector<std::thread> task_threads;
		bool fin_flag = true;

		while (fin_flag)
		{
			fin_flag = false;

			for (int i = 0; i < dim; ++i) {
				if (adj_matrix[i].size() == 0) { continue; }
				else { fin_flag = true; }

				bool edge_flag = true;
				std::vector<int> par_list;
				for (int j = 0; j < dim; ++j) {
					if (adj_matrix[i][j] == 1) { 
						edge_flag = false; 
					}
					else if(adj_matrix[i][j] == -1){
						par_list.push_back(j);
					}
				}
				if(edge_flag){ 
					for (auto par : par_list) {
						adj_matrix[par][i] = 0;
					}
					adj_matrix[i].clear();
					task_threads.push_back(std::thread(make_task, nodes[i]));
				}
			}
			for (auto &task : task_threads) {
				task.join();
			}
			task_threads.clear();
		}

	}


};


