return {version=12,pkgs={{name="noice.nvim",file="lazy.lua",source="lazy",dir="/home/codenoir/.local/share/nvim/lazy/noice.nvim",spec=function()
return {
  -- nui.nvim can be lazy loaded
  { "MunifTanjim/nui.nvim", lazy = true },
  {
    "folke/noice.nvim",
  },
}

end,},{name="plenary.nvim",file="community",source="lazy",dir="/home/codenoir/.local/share/nvim/lazy/plenary.nvim",spec={"nvim-lua/plenary.nvim",lazy=true,},},},}