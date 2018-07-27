local socket = require "socket"
local database = require "database"
local DELAY=10
local DEBUG=nil

tryaccpet=function (Door)
  --inline
	return function ()
			local conn = Door:accept()
			local delay = 0
			while (not dead) do
				if delay then
					Door:settimeout(delay)
				end
				conn = server:accept()
				if conn then
					delay = coroutine.yield(conn)
				else
					delay = coroutine.yield(nil)
				end
			end
end
  --inline
end

function alive (str) if dead~="dead" then return true else return false end end

function cli_generate(cli,recf)
  --if DEBUG then pcall(print,pcall(type,cli),cli) end
	cli:settimeout(0.001)
	return coroutine.create(
	function ()
		local state,rec,buff
		local rect = {}
		while (not dead) do
			rec,state,buff=cli:receive("*l")
			if rec then
				table.insert(rect,rec)
				else
				  if buff then
					table.insert(rect,buff)
				  end
		  	end

			if DEBUG then print(os.date(),"\n\tReceived:",rec,"state:",state,"buff:") if type(buff)=="string" then print("buff len:",string.len(buff))end end

			local len=-1
			if buff then
				if type(buff)=="string" then len = string.len(buff) end
		  	end

			if  state =="timeout" or ((not rec) and len==0)  then
				print("concat:",table.concat(rect,"\n"))
				local _,msg=pcall(recf,cli,table.concat(rect,"\n"))
				if not _ then 
					print("PCALL:",msg) 
					print("concat:",table.concat(rect,"\n"))
					recf(cli,table.concat(rect,"\n"))
				end
				rect = {}
			end
			if state == "closed" then
				return
			end
			if not rec then
			  coroutine.yield()
			end

	end
end)
end
function dispatch(clients,acp,rec,deal)
	local state,cli
	while (not dead) do
		state,cli=coroutine.resume(acp,1/(1+DELAY*clients.n))
		if not state then kill(clients)
		  print(os.date(),"guess dead")
		end
		if cli then
			table.insert(clients,deal(cli,rec))
			clients.n=clients.n+1
		end

		for i,thread in pairs(clients) do
			if not (i == "n") then 
				state,_ = coroutine.resume(thread)
			if not state then
			  	print("\t##WARN##\n",os.date(),"Thread:",i,thread,"is out\n\tR:",_)
				clients.n=clients.n-1
				clients[i]=nil
			end
			end
		end
	end
end

function kill(pool)
  for i,cli in pairs(pool) do
	if i~="n" then
		coroutine.resume(cli) 
		pool[i]=nil
		dead = true
	end
  end
end

function react (cli,data)
	local jsonstr = string.match(data,"\n([[].+[]])$")
	--local name,email,text=string.match(jsonstr,"name\" -: -\"(.+)\".+\"email\" -: -\"(.+)\".+\"text\" -: -\"(.+\"")
	for name,email,text in (
	  (
		function(json,...)
		local buffs= {}
		local mstrs={}
		--json
		--[[
		for i,str in pairs({...}) do		  
		  --if DEBUG then print("trying",str) end
			table.insert(mstrs,"\""..str.."\"[^:]-:[^\"]-\"([^\"]+)\"[^\"]-")
		end
		]]
		--html
		for i,str in pairs({...}) do		  
		  if DEBUG then print("trying",str) end
			table.insert(mstrs,str.."=([^&]+)&-")
		end
		if DEBUG then
			print("Match regx:",table.concat(mstrs))
	  	end
		for buff in string.gmatch(json,"(.+)") do
			table.insert(buffs,{})
			for i,mstr in pairs(mstrs) do
				buffs[#buffs][i]=string.match(buff,mstr)
				if DEBUG then 
				  	print("check",#buffs,buffs[#buffs])
					print("matching:",buff,mstr)
				end
			end
		end
		local state=1
		return function()
			if not buffs[state] then return nil end
			state=state+1
			return buffs[state-1][1],buffs[state-1][2],buffs[state-1][3]
		end
	end
	)(data,"name","email","text")) do
	local state,msg=pcall(Data.insert,Data,name,email,text)
	if DEBUG then print("n,e,t:",name,email,text)end
	if not state then 
	  print(msg) 
	end
	end
	part_send(cli,packit())
	--print("stats:",cli:getstats())
	print("Json:",packit(Data:json()))
	cli:send(table.concat({"\n", Data:json(),"\n"}))
	--print("send:",cli:send(packit(Data:json())))
	if DEBUG then
		print("Json:",packit(Data:json()))
  	end
	cli:close()
end

function part_send(cli,data)
  	for i in string.gmatch(data,"(.-[$\n])") do 
		print("Sending:",cli:send(i) )
	  end
	return cli
  end

function packit(content)
  local head={"HTTP/1.1 200 OK\n",
	"",
"Content-Type: text/json\n",
"Date: ",
nil,
"\nServer: Lua\n",
"Access-Control-Allow-Origin: *\n"
}
  head[5] = os.date("%a, %d %b %Y %H:%M:%S GMT")
  if content then
  return table.concat(head) .. content
else return table.concat(head)
end
end


function main()
	
	local client ={}
	client.n=0
	Data = database.load({})
	server = socket.bind("127.0.0.1","8080",1024)
	server:settimeout(0.001)
	thread_acp  = coroutine.create(tryaccpet(server))
	dispatch(client,thread_acp,react,cli_generate)
	
end


--
main()
