use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::collections::HashMap;
use std::collections::VecDeque;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

#[derive(Copy, Clone, Eq, PartialEq)]
struct Raindeer {
    cost: u64,
    position: (usize,usize),
    facing: char,
    turned: bool,
}

impl Ord for Raindeer {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost)
    }
}

impl PartialOrd for Raindeer {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn get_dir(d : char) -> (i32,i32) {
    match d {
        'v' => (1,0),
        '>' => (0,1),
        '^' => (-1,0),
        '<' => (0,-1),
        _ => (0,0),
    }
}

fn turn(d: char, r: bool) -> char {
    if r {
        match d {
            'v' => '<',
            '>' => 'v',
            '^' => '>',
            '<' => '^',
            _ => 'o',
        }
    } else {
        match d {
            'v' => '>',
            '>' => '^',
            '^' => '<',
            '<' => 'v',
            _ => 'o',
        }
    }
}

fn move_point(p: (usize,usize), v: (i32,i32)) -> (usize,usize) {
    return (((p.0 as i32) + v.0) as usize,((p.1 as i32) + v.1) as usize)
}

fn move_point_back(p: (usize,usize), v: (i32,i32)) -> (usize,usize) {
    return (((p.0 as i32) - v.0) as usize,((p.1 as i32) - v.1) as usize)
}

fn plot_paths(map: &Vec<Vec<char>>, visited: &HashSet<(usize,usize)>) {
    let n_row = map.len();
    let n_col = map[0].len();
    for r in 0..n_row {
        for c in 0..n_col {
            if visited.contains(&(r,c)) {
                print!("O");
            } else if map[r][c] != '.'{
                print!("{}",map[r][c]);
            } else {
                print!(" ");
            }
        }
        print!("\n");
    }
}

fn shortest_path(start: Raindeer, map: &Vec<Vec<char>>, to_plot : bool) -> (u64,usize) {
    let mut visited : HashMap<((usize,usize),char),u64> = HashMap::new();
    let mut queue = BinaryHeap::new();
    let mut best: u64 = 0;
    queue.push(start);
    let mut best_paths: HashSet<(usize,usize)> = HashSet::new();
    let mut paths: VecDeque<((usize,usize),char)> = VecDeque::new();
    let mut ind : usize = 0;
    while let Some(Raindeer{cost, position, facing, turned}) = queue.pop() {
        ind += 1;
        if ind % 1000 == 0 {
            println!("Look at deer on pos {:?}, facing {}, cur cost {}, we have {} in queue",position, facing,cost,queue.len());
        }

        if map[position.0][position.1] == 'E' {
            best = cost;
            paths.push_back((position,facing));
            *visited.entry((position,facing)).or_insert(0) = cost;
            break;    
        }

        if visited.contains_key( &(position,facing) ) {
            if cost > *visited.get(&(position,facing)).unwrap() {
                continue;
            }
        } 
        *visited.entry((position,facing)).or_insert(0) = cost;
        // Prova att gå framåt
        let forward = get_dir(facing);
        let next: (usize,usize) = move_point(position, forward);
        if map[next.0][next.1] != '#' {
            queue.push(Raindeer{ cost: cost + 1, position: next, facing: facing, turned: false });
            
        }

        if !turned {
            let left = get_dir(turn(facing, false));
            let next_left: (usize,usize) = move_point(position, left);
            if map[next_left.0][next_left.1] != '#' {
                queue.push(Raindeer{ cost: cost + 1000, position: position, facing: turn(facing, false), turned: true });
            }
            let right = get_dir(turn(facing, true));
            let next_right: (usize,usize) = move_point(position, right);
            if map[next_right.0][next_right.1] != '#' {
                queue.push(Raindeer{ cost: cost + 1000, position: position, facing: turn(facing, true), turned: true });
            }
        }

    }
    

    while !paths.is_empty() {
        let (pos,d) = paths.pop_front().unwrap();
        best_paths.insert(pos);
        let cur: u64 = *visited.get(&(pos,d)).unwrap();
        // Move Backwards
        let new_pos = move_point_back(pos,get_dir(d));
        if visited.contains_key(&(new_pos,d)) {
            if cur == (visited.get(&(new_pos,d)).unwrap()+1) {
                paths.push_back((new_pos,d));
            } 
        }
        // Turn right
        let d_r = turn(d,false);
        if visited.contains_key(&(pos,d_r)) {
            if cur == (visited.get(&(pos,d_r)).unwrap() + 1000) {
                paths.push_back((pos,d_r));
            } 
        }
        // Turn left
        let d_l = turn(d,true);
        if visited.contains_key(&(pos,d_l)) {
            if cur == (visited.get(&(pos,d_l)).unwrap() + 1000) {
                paths.push_back((pos,d_l));
            } 
        }
    }
    if to_plot {plot_paths(&map, &best_paths);}

    return (best, best_paths.len());
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    let mut to_plot: bool = false;
    if args.len() <= 1 {
        return Ok(());
    }
    if args.len() > 2 {
        to_plot = true;
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    let char_matrix : Vec<Vec<char>> = lines.into_iter().map(|line| line.chars().collect()).collect();
    let num_row : usize = char_matrix.len();
    let num_col : usize = char_matrix[0].len();
    let mut starting_deer : Raindeer = Raindeer{cost: 0, position: (0,0), facing: 'o', turned: false};
    for r in 0..num_row {
        for c in 0..num_col {
            if char_matrix[r][c] == 'S' {
                starting_deer = Raindeer{cost: 0, position: (r, c), facing: '>', turned: false};
            }
        }
    }   
    

    let (ans_a, ans_b) = shortest_path(starting_deer, &char_matrix, to_plot);
    
   
    println!("Answer part A: {}", ans_a);
    
    println!("Answer part B: {}", ans_b);
    Ok(())
}
