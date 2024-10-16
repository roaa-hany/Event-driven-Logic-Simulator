`timescale 1ns / 1ps

module circuit_2(input a, input b, input c, output o);

    wire w, y, n;
    
    not #(2) (n,b);
    and #(5) (w,a,n);
    buf #(1) (y,w);
    nor #(7) (o,y,c);

endmodule
