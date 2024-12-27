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

// struct Wire<'a> {
//     name: &'a str,
//     value: Option<bool>,
// }

struct Gate<'a> {
    lhs: &'a str,
    rhs: &'a str,
    out: &'a str,
    logic: &'a str,
}

fn run_calc(mut wire_map: HashMap<&str, Option<usize>>, gate_vec: &Vec<Gate>) -> usize {

    let mut changed: bool = true;
    let mut indx: usize = 0;
    while changed {
        let mut num_none = 0;
        indx += 1;
        changed = false;
        for g in gate_vec {
            let out_val = wire_map.get(g.out).unwrap();
            let lhs_val = wire_map.get(g.lhs).unwrap();
            let rhs_val = wire_map.get(g.rhs).unwrap();
            if out_val.is_none() {
                num_none += 1;
                changed = true;
                if !lhs_val.is_none() && !rhs_val.is_none() {
                    if g.logic == "AND" {
                        *wire_map.get_mut(g.out).unwrap() = Some( lhs_val.unwrap() & rhs_val.unwrap() );
                    } else if g.logic == "OR" {
                        *wire_map.get_mut(g.out).unwrap() = Some( lhs_val.unwrap() | rhs_val.unwrap() );
                    } else if g.logic == "XOR" {
                        *wire_map.get_mut(g.out).unwrap() = Some( lhs_val.unwrap() ^ rhs_val.unwrap() );
                    } else {
                        //println!("Fel här!");
                    }
                }
            }
        }
        if indx % 1000 == 0 {println!("{} - {}",indx, num_none)};

    }
    let mut output: usize = 0;
    for (name, val) in &wire_map {
        if name.starts_with("z") {
            let base_2: usize = 2;
            let bit = name[1..].parse::<u32>().unwrap();
            //println!("{} - {:?}", bit, val);
            if *val == Some(1) {
                output += base_2.pow(bit);
            }
        }
    }
    return output;
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
    let mut wire_map: HashMap<&str,Option<usize>> = HashMap::new();
    let mut gate_vec: Vec<Gate> = Vec::new();
    for line in lines {
        if line.len() == 0 {continue}
        let line_vec = line.split(" -> ").collect::<Vec<_>>();
        if line_vec.len() > 1 {
            let out = line_vec[1];
            let lhs_vec: Vec<&str> = line_vec[0].split(" ").collect();
            let lhs = lhs_vec[0];
            let rhs = lhs_vec[2];
            let logic = lhs_vec[1];
            let gate: Gate = Gate{lhs: lhs, rhs: rhs, out: out, logic: logic};
            gate_vec.push(gate);
            if !wire_map.contains_key(lhs) {
                wire_map.insert(lhs, None);
            }
            if !wire_map.contains_key(rhs) {
                wire_map.insert(rhs, None);
            }
            if !wire_map.contains_key(out) {
                wire_map.insert(out, None);
            }
        } else {
            let wire_vec: Vec<&str> = line.split(": ").collect();
            wire_map.insert(wire_vec[0], Some(wire_vec[1].parse::<usize>().unwrap()));
        }
    }
    // println!("{}",wire_map.len());
    // println!("{}",gate_vec.len());

    let ans_a = run_calc(wire_map.clone(), &gate_vec);
    println!("Answer part A: {}", ans_a);

    let mut x_val = 0;
    let mut y_val = 0;
    for (name, val) in &wire_map {
        if name.starts_with("x") {
            let base_2: usize = 2;
            let bit = name[1..].parse::<u32>().unwrap();
            //println!("{} - {:?}", bit, val);
            if *val == Some(1) {
                x_val += base_2.pow(bit);
            }
        }
        if name.starts_with("y") {
            let base_2: usize = 2;
            let bit = name[1..].parse::<u32>().unwrap();
            //println!("{} - {:?}", bit, val);
            if *val == Some(1) {
                y_val += base_2.pow(bit);
            }
        }
    }

    let mut rule_1_vec: Vec<usize> = Vec::new();
    let mut rule_2_vec: Vec<usize> = Vec::new();

    let mut ans_b_vec: Vec<&str> = Vec::new();

    for i in 0..gate_vec.len() {
        if gate_vec[i].out.starts_with("z") && (gate_vec[i].logic != "XOR") && (gate_vec[i].out != "z45") {
            rule_1_vec.push(i);
            //println!("{} {} {} -> {}",gate_vec[i].lhs, gate_vec[i].logic, gate_vec[i].rhs, gate_vec[i].out);
            ans_b_vec.push(gate_vec[i].out);
        }
        if (!(gate_vec[i].lhs.starts_with("x") || gate_vec[i].lhs.starts_with("y")) && !(gate_vec[i].rhs.starts_with("y") || gate_vec[i].rhs.starts_with("x")) && !gate_vec[i].out.starts_with("z")) && gate_vec[i].logic == "XOR" {
            rule_2_vec.push(i);
            ans_b_vec.push(gate_vec[i].out);
            //println!("{} {} {} -> {}",gate_vec[i].lhs, gate_vec[i].logic, gate_vec[i].rhs, gate_vec[i].out);
        }
    }

    for r1 in &rule_1_vec {
        let number = &gate_vec[*r1].out[1..];
        for r2 in &rule_2_vec {
            let lhs = &gate_vec[*r2].lhs;
            let rhs = &gate_vec[*r2].rhs;
            for g in &gate_vec {
                if g.out == *lhs || g.out == *rhs {
                    if g.logic == "XOR" && g.lhs[1..] == *number {
                        let out = gate_vec[*r1].out;
                        gate_vec[*r1].out = gate_vec[*r2].out;
                        gate_vec[*r2].out = out;
                        break
                    }
                }
            }
        }
    }

    let new_val = run_calc(wire_map.clone(), &gate_vec);

    //println!("{}", new_val);

    //println!("{}", new_val ^ (x_val+y_val));

    let mut error = new_val ^ (x_val+y_val);
    let mut bit = 0;
    while error > 1 {
        error /= 2;
        bit += 1;
    }
    let bit_string = format!("{:02}", bit);

    //println!("{} - {}",bit,bit_string);
    let mut indx: usize = 0;
    let mut out_swap: &str = "";
    let mut found: bool = false;
    for i in 0..gate_vec.len() {
        if gate_vec[i].lhs[1..] == bit_string {
            ans_b_vec.push(gate_vec[i].out);
            if !found {
                indx = i;
                out_swap = gate_vec[i].out;
                found = true;
            } else {
                gate_vec[i].out = gate_vec[indx].out;
                gate_vec[indx].out = out_swap;
                break
            }
        }
    }
    ans_b_vec.sort();
    let ans_b = ans_b_vec.join(",");
    println!("Answer part B: {}", ans_b);
    Ok(())
}
