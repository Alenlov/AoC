use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn get_dir(d : usize) -> (i32,i32) {
    match d {
        0 => (1,0),
        1 => (0,1),
        2 => (-1,0),
        3 => (0,-1),
        _ => (0,0),
    }
}

fn move_point(p: (usize,usize), v: (i32,i32)) -> (i32,i32) {
    return (((p.0 as i32) + v.0),((p.1 as i32) + v.1))
}

fn is_valid(p: (i32,i32), max_pos: (usize, usize)) -> bool {
    return (p.0 >= 0) && (p.0 < (max_pos.0 as i32)) && (p.1 >= 0) && (p.1 < (max_pos.1 as i32))
}

fn find_path(start: (usize, usize), end: (usize, usize), map : &Vec<Vec<char>>) -> HashMap<(usize,usize),usize> {
    let mut dists: HashMap<(usize,usize),usize> = HashMap::new();
    let max_pos = (map.len(), map[0].len());
    dists.insert(start,0);
    let mut cur: (usize,usize) = start;
    while cur != end {
        for d in 0..4 {
            let new_pos = move_point(cur, get_dir(d));
            if is_valid(new_pos, max_pos) {
                let new_pos_u = (new_pos.0 as usize, new_pos.1 as usize);
                if map[new_pos_u.0][new_pos_u.1] != '#' && !dists.contains_key(&new_pos_u) {
                    dists.insert(new_pos_u, *dists.get(&cur).unwrap()+1);
                    cur = new_pos_u;
                    break;
                }
            }
        }
    }
    return dists;
}

// fn find_cheats_a(map: &Vec<Vec<char>>, dists: &HashMap<(usize,usize),usize>) -> HashMap<usize,usize> {
//     let mut cheats: HashMap<usize,usize> = HashMap::new();
//     let max_pos = (map.len(), map[0].len());
//     for (pos, val) in dists {
//         for d1 in 0..4 {
//             let new_pos_1 = move_point(*pos, get_dir(d1));
//             if is_valid(new_pos_1, max_pos) {
//                 let new_pos_u_1 = (new_pos_1.0 as usize, new_pos_1.1 as usize);
//                 if map[new_pos_u_1.0][new_pos_u_1.1] == '#' {
//                     for d2 in 0..4 {
//                         let new_pos_2 = move_point(new_pos_u_1, get_dir(d2));
//                         if is_valid(new_pos_2, max_pos) {
//                             let new_pos_u_2 = (new_pos_2.0 as usize, new_pos_2.1 as usize);
//                             if dists.contains_key(&new_pos_u_2) {
//                                 let new_val = *dists.get(&new_pos_u_2).unwrap();
//                                 if new_val > *val {
//                                     let saving = new_val - val - 2;
//                                     cheats.entry(saving).and_modify(|v| *v += 1).or_insert(1);
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return cheats;
// }

fn dist(p1:(usize,usize), p2:(usize,usize)) -> usize {
    let d0: i32 = p1.0 as i32 - p2.0 as i32;
    let d1: i32 = p1.1 as i32 - p2.1 as i32;
    return (d0.abs() +d1.abs()) as usize
}

// fn find_cheats(map: &Vec<Vec<char>>, dists: &HashMap<(usize,usize),usize>, max_dist: usize) -> HashMap<usize,usize> {
//     let mut cheats: HashMap<usize,usize> = HashMap::new();
//     let max_pos = (map.len(), map[0].len());
//     for (pos, val) in dists {
//         let mut ends_in: HashSet<(usize,usize)> = HashSet::new();
//         let mut visited: HashSet<(usize,usize)> = HashSet::new();
//         let mut heads: VecDeque<(usize,usize)> = VecDeque::new();
//         heads.push_back(*pos);
//         visited.insert(*pos);
//         while let Some(cur) = heads.pop_front() {
//             //println!("{}",heads.len());
//             let cur_dist = dist(*pos,cur);
//             if map[cur.0][cur.1] != '#' && !ends_in.contains(&cur){
//                 let new_val = *dists.get(&cur).unwrap();
//                 if new_val >= *val + cur_dist{
//                     let saving = new_val - val - cur_dist;
//                     cheats.entry(saving).and_modify(|v| *v+=1).or_insert(1);
//                     ends_in.insert(cur);
//                 }
//             }
//             if cur_dist < max_dist {
//                 for d in 0..4 {
//                     let new_pos = move_point(cur, get_dir(d));
//                     if is_valid(new_pos, max_pos) {
//                         let new_pos_u = (new_pos.0 as usize, new_pos.1 as usize);
//                         if !visited.contains(&new_pos_u) {
//                             heads.push_back(new_pos_u);
//                             visited.insert(new_pos_u);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return cheats;
// }

fn num_cheats(dists: &HashMap<(usize,usize),usize>, max_dist: usize) -> HashMap<usize,usize> {
    let mut cheats: HashMap<usize,usize> = HashMap::new();
    let mut dist_counts: usize = 0;
    for (pos_1, val_1) in dists {
        for (pos_2, val_2) in dists {
            if val_2 < val_1 {continue}
            dist_counts += 1;
            if dist(*pos_1,*pos_2) <= max_dist {
                if val_1 + dist(*pos_1,*pos_2) < *val_2 {
                    let saving = *val_2 - *val_1 - dist(*pos_1,*pos_2);
                    cheats.entry(saving).and_modify(|v| * v+= 1).or_insert(1);
                }
            }
        }
    }
    println!("{}",dist_counts);
    return cheats;
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
    let map : Vec<Vec<char>> = lines.into_iter().map(|line| line.chars().collect()).collect();
    let num_row : usize = map.len();
    let num_col : usize = map[0].len();
    let mut start_pos: (usize,usize) = (0,0);
    let mut end_pos: (usize,usize) = (0,0);
    for r in 0..num_row {
        for c in 0..num_col {
            if map[r][c] == 'S' {
                start_pos = (r,c);
            } else if map[r][c] == 'E' {
                end_pos = (r,c);
            }
        }
    }   
    

    let route: HashMap<(usize,usize),usize> = find_path(start_pos, end_pos, &map);
    let cheats: HashMap<usize,usize> = num_cheats(&route, 2);
    let cheats2: HashMap<usize,usize> = num_cheats(&route, 20);
    let mut ans_a: usize = 0;
    let mut ans_b: usize = 0;
    for (save, num) in cheats {
        if save >= 100 {
            ans_a += num;
        }
    }
    for (save, num) in cheats2 {
        
        if save >= 100 {
            ans_b += num;
        }
    }
    println!("Answer part A: {}", ans_a);
    
    println!("Answer part B: {}", ans_b);

    //println!("Num steps tot: {:?}",*route.get(&end_pos).unwrap());

    
    Ok(())
}
