`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2024 12:50:22 PM
// Design Name: 
// Module Name: circuit_2
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module circuit_2();
    input a,b,c;
    output o;
    wire w1, bW1, nB;
    
    not (nB, b);
    and (w1, a, nB);
    buf (bW1, w1);
    nor(o, bW1, c);

endmodule
