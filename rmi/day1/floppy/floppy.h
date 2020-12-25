#include <string>
#include <vector>

void read_array(int subtask_id, const std::vector<int> &v);

void save_to_floppy(const std::string &bits);

std::vector<int> solve_queries(int subtask_id, int N, const std::string &bits,
                               const std::vector<int> &a,
                               const std::vector<int> &b);
