use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::collections::VecDeque;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn get_dir(d : i32) -> (i32,i32) {
    match d {
        0 => (1,0),
        1 => (0,1),
        2 => (-1,0),
        3 => (0,-1),
        _ => (0,0),
    }
}

fn dir_to_side(d : (i32,i32)) -> char {
    match d {
        (1,0) => 'd',
        (-1,0) => 'u',
        (0,1) => 'r',
        (0,-1) => 'l',
        _ => 'o',
    }
}

fn side_to_dir(d : char) -> (usize,usize) {
    match d {
        'd' => (0,1),
        'u' => (0,1),
        'l' => (1,0),
        'r' => (1,0),
        _ => (0,0),
    }
}

fn explore_area(p : (usize,usize), map : &Vec<Vec<char>>) -> (u64, u64, HashSet<(usize,usize)>) {
    let mut area : HashSet<(usize,usize)> = HashSet::new();
    let cur : char = map[p.0][p.1];
    let mut heads : VecDeque<(usize,usize)> = VecDeque::new();
    let mut sides : Vec<(char,(usize,usize))> = Vec::new();
    let mut side_num : u64 = 0;
    let mut border : u64 = 0;
    heads.push_back(p);
    let max_r : i32 = map.len() as i32;
    let max_c : i32 = map[0].len() as i32;
    while !heads.is_empty() {
        let h : (usize,usize) = heads.pop_front().unwrap();
        if !area.contains(&h) {
            area.insert(h);
            for d in 0..4 {
                let dir : (i32,i32) = get_dir(d);
                let new_r = (h.0 as i32) + dir.0;
                let new_c = (h.1 as i32) + dir.1;
                let mut hit_border : bool = false;
                if (new_r < 0) || (new_r >= max_r) || (new_c < 0) || (new_c >= max_c) {
                    hit_border = true;
                } else {
                    if cur == map[new_r as usize][new_c as usize] {
                        heads.push_back( (new_r as usize, new_c as usize) );
                    } else {
                        hit_border = true;
                    }
                }
                if hit_border {
                    border += 1;
                    sides.push((dir_to_side(dir),h));
                }
            }
        }
    }
    sides.sort_by(|a, b| {
        if a.0 != b.0 {
            return (b.0).cmp(&(a.0));
        } else {
            if a.0 == 'u' || a.0 == 'd' {
                if (a.1).0 != (b.1).0 {return ( (a.1).0 ).cmp( &(b.1).0 );}
                else {return ( (a.1).1 ).cmp( &(b.1).1 );}
            } else {
                if (a.1).1 != (b.1).1 {return ( (a.1).1 ).cmp( &(b.1).1 );}
                else {return ( (a.1).0 ).cmp( &(b.1).0 );}
            }
        }
    });
    let mut t : char = '0';
    let mut p : (usize,usize) = (0,0);
    for i in 0..sides.len() {
        let (new_t, new_p) = sides[i];
        if t == '0' {
            t = new_t;
            p = new_p;
            side_num += 1;
            continue;
        } else if t == new_t {
            let dir : (usize,usize) = side_to_dir(t);
            if !((p.0+dir.0 == new_p.0) && (p.1+dir.1 == new_p.1)) {
                side_num += 1;
            }
        } else {
            side_num += 1;
        }

        t = new_t;
        p = new_p;
    }

    //println!("Area containing {} has a border of {} and area {} and side_num {}",cur,border,area.len(),side_num);
    return (border, side_num, area);
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
    let char_matrix : Vec<Vec<char>> = lines.into_iter().map(|line| line.chars().collect()).collect();
    
    let num_row : usize = char_matrix.len();
    let num_col : usize = char_matrix[0].len();

    let mut explored : HashSet<(usize,usize)> = HashSet::new();

    let mut ans_a: u64 = 0;
    let mut ans_b: u64 = 0;

    for r in 0..num_row {
        for c in 0..num_col {
            if !explored.contains(&(r,c))
            {
                // Utforska detta område
                let (border, sides, area) = explore_area( (r,c), &char_matrix );
                ans_a += border * (area.len() as u64);
                ans_b += sides * (area.len() as u64);
                for p in area {
                    explored.insert(p);
                }
                // När klar lägg till området i explored
            }
        }
    }
   
    println!("Answer part A: {}", ans_a);
    
    println!("Answer part B: {}", ans_b);
    Ok(())
}
