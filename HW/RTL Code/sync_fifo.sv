module synchronous_fifo #(parameter DEPTH=8, DATA_WIDTH=8) (
  input clk, rst_n,
  input w_en, r_en,
  input [DATA_WIDTH-1:0] data_in,
  output logic [DATA_WIDTH-1:0] data_out,
  output full, empty
);

logic [DATA_WIDTH-1:0] buffer [0:DEPTH-1]; 

//wr and rd pointers (need extra bit)
logic [$clog2(DEPTH):0] wr_ptr;
logic [$clog2(DEPTH):0] rd_ptr;

assign full = (wr_ptr[$clog2(DEPTH)-1:0] == rd_ptr[$clog2(DEPTH)-1:0]) && 
              (wr_ptr[$clog2(DEPTH)] != rd_ptr[$clog2(DEPTH)]);
assign empty = (wr_ptr == rd_ptr);

//write
always_ff @(posedge clk or negedge rst_n) begin
    if(!rst_n)begin
      //reset conditions
      wr_ptr <= '0;
    end
    else if(w_en && !full)begin
      buffer[wr_ptr[$clog2(DEPTH)-1:0]] <= data_in;
      wr_ptr <= wr_ptr + 1'b1;
    end
end

//read
always_ff @(posedge clk or negedge rst_n) begin
    if(!rst_n)begin
      //reset conditions
      rd_ptr <= '0;
      data_out <= '0;
    end
    else if(r_en && !empty)begin
      data_out <= buffer[rd_ptr[$clog2(DEPTH)-1:0]];
      rd_ptr <= rd_ptr + 1'b1;
    end
end

endmodule