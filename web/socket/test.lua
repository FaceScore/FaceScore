sock=require	"socket"
function start()
	thread = {}
	server = sock.bind("127.0.0.1","8080")
	server:settimeout(0.01)
	table.insert(thread,coroutine.create(
	function ()
		while (true) do
			local cli,_=server:accept()
			if cli then
				print("Test:",cli,_)
				cli:settimeout(0.01)
--				local ccli = cli
				table.insert(thread,coroutine.create(
				function()
--					local cli=ccli
					while (true) do
						rec,stats,buff = cli:receive()
						if rec then
							print("cli:",cli,"rec:",rec)
							print(cli,"send",cli:send("what ever we reply" ..'\n'))
						else
							if buff then
								if ((({pcall(string.len,buff)})[2])<1) then
									coroutine.yield()
								else
									print("something happened,buff:",buff)
									if (state=="timeout") then
										coroutine.yield()
									end
									if (state=="closed") then
										return
									end
									print(cli,"send",cli:send("what ever we reply" ..'\n'))
								end
							end
						end
					end	
				end
			))
			end
			coroutine.yield()
		end
	end	))
	while (true)  do
		for i,v in pairs(thread) do 
			state={pcall(coroutine.resume,v)}
			if  not state[2] then
				state[1]=""
				state[2]=""
				print("id:",i,table.concat(state))
				thread[i]=nil
			end
		end
	end
end
start()