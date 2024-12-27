use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;
use std::collections::HashSet;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn find_biggest<'a>(start: &'a str, graph: &'a HashMap<&'a str, HashSet<&'a str>>) -> Vec<&'a str> {
    let mut max_clique: Vec<&str> = Vec::new();
    let mut con_set: HashSet<&str> = graph.get(start).unwrap().clone();
    let mut visited: HashSet<&str>;
    while con_set.len() > 0 {
        visited = HashSet::from([start]);
        for con in &con_set {
            let mut to_add: bool = true;
            for v in &visited {
                if !graph.get(v).unwrap().contains(con) {
                    to_add = false;
                    break
                }
            }
            if to_add {
                visited.insert(con);
            }
        }
        let mut cur_clique: Vec<&str> = visited.clone().into_iter().collect();
        cur_clique.sort();
        if cur_clique.len() > max_clique.len() {
            max_clique = cur_clique;
        }
        for v in &visited {
            if con_set.contains(v) {
                con_set.remove(v);
            }
        }
    }

    return max_clique
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    
    let mut connections: HashMap<&str,HashSet<&str>> = HashMap::new();

    for line in lines {
        let con: Vec<&str> = line.split("-").collect();
        connections.entry(con[0]).and_modify(|c| { c.insert(con[1]); }).or_insert(HashSet::from([con[1]]));
        connections.entry(con[1]).and_modify(|c| { c.insert(con[0]); }).or_insert(HashSet::from([con[0]]));
    }

    
    let mut groups: HashSet<Vec<&str>> = HashSet::new();

    for (comp, cons) in &connections {
        if comp.starts_with("t") {
            for oth1 in cons {
                for oth2 in cons {
                    if oth1 != oth2 {
                        if connections.get(oth1).unwrap().contains(oth2) {
                            let mut tri_vec = vec![*comp,*oth1,*oth2];
                            tri_vec.sort();
                            groups.insert( tri_vec);
                        }
                    }
                }
            }
        }
    }

    let ans_a: usize = groups.len();

    println!("Answer part A: {}", ans_a);

    let mut ans_b: String = String::from("");

    for (k, _) in &connections {
        let maximal_clique: Vec<&str> = find_biggest(k, &connections);
        let test_ans_b = maximal_clique.join(",");
        if test_ans_b.len() > ans_b.len() {
            ans_b = test_ans_b;
        }
    }

    println!("Answer part B: {}", ans_b);
    Ok(())
}
