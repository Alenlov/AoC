use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;
use std::collections::HashSet;
use std::collections::VecDeque;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn get_dir(d:i32) -> (i32,i32) {
    match d {
        0 => (1,0),
        1 => (-1,0),
        2 => (0,1),
        3 => (0,-1),
        _ => (0,0),
    }
}

fn move_point(p:(i32,i32), d:(i32,i32)) -> (i32,i32) {
    return (p.0+d.0, p.1+d.1)
}

fn is_within(p:(i32,i32), x_range: (i32,i32), y_range: (i32,i32)) -> bool {
    return (p.0 <= x_range.1 && p.0 >= x_range.0) && (p.1 <= y_range.1 && p.1 >= y_range.0)
}

fn shortest_path(walls: &HashSet<(i32,i32)>, start: (i32,i32), end: (i32,i32)) -> (Option<i32>,HashSet<(i32,i32)>) {
    let mut heads: VecDeque<(i32,i32)> = VecDeque::new();
    let mut visited: HashMap<(i32,i32),i32> = HashMap::new();
    let x_range = (start.0,end.0);
    let y_range = (start.1,end.1);
    heads.push_back(start);
    visited.insert(start,0);
    while let Some(h) = heads.pop_front() {
        for d in 0..4 {
            let new_h = move_point(h, get_dir(d));
            if !visited.contains_key(&new_h) {
                if !walls.contains(&new_h) {
                    if is_within(new_h, x_range, y_range) {
                        visited.insert(new_h, visited.get(&h).unwrap()+1);
                        heads.push_back(new_h);
                    }
                }
            }
        }
    }
    let mut best_path: HashSet<(i32,i32)> = HashSet::new();
    if !visited.get(&end).is_none() {
        best_path.insert(end);
        let mut cur_pos = end;
        let mut cur_val = *visited.get(&end).unwrap();
        while cur_pos != start {
            let mut new_pos:(i32,i32);
            for d in 0..4 {
                new_pos = move_point(cur_pos, get_dir(d));
                if visited.contains_key(&new_pos) {
                    if *visited.get(&new_pos).unwrap() + 1 == cur_val {
                        cur_pos = new_pos;
                        cur_val -= 1;
                        best_path.insert(cur_pos);
                        break
                    }
                }
            }
        }
    }
    return (visited.get(&end).copied(),best_path);
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    //let mut to_plot: bool = false;
    if args.len() <= 1 {
        return Ok(());
    }
    /*if args.len() > 2 {
        to_plot = true;
    }*/
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);

    // For A:
    let mut walls: HashSet<(i32,i32)> = HashSet::new();

    let max_x = 70;
    let max_y = 70;

    let mut ans_a: i32 = 0;
    let mut ans_b: (i32,i32) = (0,0);

    let mut best_path: HashSet<(i32,i32)>;

    (_, best_path) = shortest_path(&walls, (0,0), (max_x,max_y));
    let mut cntr: usize = 0;
    for i in 0..lines.len() {
        
        if i == 1024 {
            ans_a = shortest_path(&walls, (0,0), (max_x,max_y)).0.unwrap();
        }
        let coords: Vec<&str> = lines[i].split(',').collect();
        let x: i32 = coords[0].parse::<i32>().unwrap();
        let y: i32 = coords[1].parse::<i32>().unwrap();
        walls.insert((x,y));
        if best_path.contains(&(x,y)) {
            cntr += 1;
            (_, best_path) = shortest_path(&walls, (0,0), (max_x,max_y));
            if !best_path.contains(&(max_x,max_y)) {
                ans_b = (x,y);
                break;
            }
        }
        
    }
    


    
    println!("Answer part A: {}", ans_a);
    
    println!("Answer part B: {},{}", ans_b.0,ans_b.1);

    println!("Number of algorithm calls, {}",cntr);
    Ok(())
}
