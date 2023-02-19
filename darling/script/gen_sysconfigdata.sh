# My understanding is that the _sysconfigdata.py 
# file is suppose to be generated, but I wasn't
# able to figure out how to do that.

#TODO: Figure out how to programatically convert
# the output to the Python friendly Dict.

pushd "../../2.7/Python-2.7.16"
python Lib/sysconfig.py > _sysconfigdata.py
popd
