-- database --
-- Index init
local id="id"
local name="name"
local email="email"
local text="text"
-- Index init over
local database = {}
database.load =function (self,name)
  if not name then name = "base.dat" end
  local file = io.open(name)
  if not file then
    self.id = 0
    self.name = {}
    self.email = {}
    self.text = {}
    return database.init(self)
  end
  self = loadstring("return "..file:read("*a"))()
  assert(self)
  return database.init(self)
end

database.init = function(self)
  return setmetatable(self, {__index=database})
end
local function safeit(x)
	return string.gsub(x,"([\"\\]","\\%1")
end


database.insert = function(self,name,email,text)
  if not name then return end
  if not email then return end
  if not text then return end

  self.id = self.id + 1
  local id = self.id
  self.name[id] = safeit(name)
  self.email[id] = safeit(email)
  self.text[id] = safeit(text)
  return self
end

database.json = function(self)
  local t_json = {}
  table.insert(t_json,"[")
  table.insert(t_json,"")
  for i = 1,self.id do
	table.insert(t_json,"{")
    for _,x in pairs ({name,email,text}) do
      (function(x)
      table.insert(t_json,"\"")
      table.insert(t_json,x)
      table.insert(t_json,"\"  : \"")
      table.insert(t_json,self[x][i])
      table.insert(t_json,"\"")
      table.insert(t_json,",")
    end)(x)
    end
    t_json[#t_json] = "}"
    table.insert(t_json,",")
  end
  t_json[#t_json] = "]"
  return table.concat(t_json)
end

database.save = function (self,filename)
  local data = {"{"}
  table.insert(data,"[\"id\"] = " .. self.id .." ,\n");
  (function (...)
    for _,x in pairs(...) do
      table.insert(data,"[\"")
      table.insert(data,x)
      table.insert(data,"\"] = \n\t{")
      for i,v in pairs(self[x]) do
        table.insert(data,"[")
        table.insert(data,i)
        table.insert(data,"] = \"")
        table.insert(data,v)
        table.insert(data,"\"\n")
        table.insert(data,",")
      end
      data[#data]="}\n"
      table.insert(data,",")
    end
  end)({name,email,text})
  data[#data]="\n}"
  local writedata = table.concat(data)
  if filename then
    local file = io.open(filename,"w")
    assert(file:write(writedata))
    file:close()
    return true,writedata
  end
  return false,writedata
end
-- database done --
return database
